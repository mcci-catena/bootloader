# MCCI Trusted Bootloader for STM32L0 with Firmware Update

<!--
  This TOC uses the VS Code markdown TOC extension AlanWalk.markdown-toc.
  We strongly recommend updating using VS Code, the markdown-toc extension and the
  bierner.markdown-preview-github-styles extension. Note that if you are using
  VS Code 1.29 and Markdown TOC 1.5.6, https://github.com/AlanWalk/markdown-toc/issues/65
  applies -- you must change your line-ending to some non-auto value in Settings>
  Text Editor>Files.  `\n` works for me.
-->
<!-- markdownlint-disable MD033 MD004 -->
<!-- markdownlint-capture -->
<!-- markdownlint-disable -->
<!-- TOC depthFrom:2 updateOnSave:true -->

- [Introduction](#introduction)
	- [Limitations](#limitations)
- [MCCI / STM32L0 Deployment Details](#mcci--stm32l0-deployment-details)
	- [SPI flash layout](#spi-flash-layout)
	- [Bootloader RAM layout](#bootloader-ram-layout)
	- [EEPROM usage](#eeprom-usage)
	- [Abstraction Layer](#abstraction-layer)
	- [Application Image Structure](#application-image-structure)
	- [AppInfo overview](#appinfo-overview)
	- [Signature block overview](#signature-block-overview)
	- [Signature Verification](#signature-verification)
	- [Programming app image from SPI](#programming-app-image-from-spi)
	- [Checking signatures](#checking-signatures)
- [The bootloader query API on ARMv6-M systems](#the-bootloader-query-api-on-armv6-m-systems)
	- [Get Update-Flag Pointer](#get-update-flag-pointer)
	- [Initialize hash buffer](#initialize-hash-buffer)
	- [Hash blocks](#hash-blocks)
	- [Finish a hash operation](#finish-a-hash-operation)
- [Bootloader States](#bootloader-states)
- [Practical Details](#practical-details)
	- [SPI flash initialization](#spi-flash-initialization)
	- [Generating public/private key pairs](#generating-publicprivate-key-pairs)
	- [Building](#building)
		- [Windows Build Example](#windows-build-example)
	- [Installing the bootloader](#installing-the-bootloader)
	- [STM32L0 Watchdog timer](#stm32l0-watchdog-timer)
- [Meta](#meta)
	- [License](#license)
	- [Support Open Source Hardware and Software](#support-open-source-hardware-and-software)
	- [Trademarks](#trademarks)

<!-- /TOC -->
<!-- markdownlint-restore -->
<!-- Due to a bug in Markdown TOC, the table is formatted incorrectly if tab indentation is set other than 4. Due to another bug, this comment must be *after* the TOC entry. -->

## Introduction

The MCCI&reg; trusted bootloader provides enhanced system integrity for IoT devices, by confirms system integrity at startup, and allowing field updating STM32L0 systems using public-key authentication of the firmware images.

The bootloader is designed with makers, subject matter experts, and experimenters in mind, so that it is easy to deploy open-source field-updatable devices based on small CPUs like the STM32L0. It is readily integrated with the Arduino IDE or other build environments.

Although it is *not* a "secure bootloader" in the commonly accepted sense, it is a trusted bootloader in the following sense:

- Barring physical access to the device, and provided the bootloader has been write protected in the STM32L0 option registers, it is reasonably certain that the bootloader will not launch an application whose image has been corrupted.
- The bootloader will authenticate and atomically update firmware from one image to another, while running unattended in the field. Power failures in the middle of an update will simply slow down the process.
- Barring physical access to the device, the bootloader will not install images that have not been signed by the trusted private key.
- The bootloader allows the system engineer to provision a fallback image that can be used in case the installed application image is corrupt; this image can be write protected, and is separate from the "field update" image.
- The normal workflow is simple and unobtrusive.
- The code is simple and easily audited.
- The cryptographic code is identically the simple and auditable public-domain TweetNaCl package, without any source changes.

Its hardware requirements are modest. Beyond an STM32L0 CPU, it requires an external storage device large enough to store the fallback image and the update image. The bootloader itself is 10k, though we allow up to 20k for future growth.

We've attempted to code the boot loader for clarity and ease of understanding and review. No conditional compiles are used in the C files. The bootloader supplies its own link script. A "platform interface" structure separates the business logic of the bootloader from the low-level hardware-dependent functions.

The bootloader manages firmware update from SPI flash; it is the application's job to get the data into the SPI flash.

Hashing and signature-verification functions are provided by the "TweetNaCl" library, via the "MCCI TweetNaCl" library.

We try to make the bootloader's operations *explicit* rather than depending on *implicit* behavior. For example, the bootloader does not use the normal C runtime startup, but is rather invoked directly from the reset vector of the bootloader. The bootloader and the linker script cooperate so that RAM variables (and RAM-based code) get initialized very early in the boot.

The bootloader requires a 64-byte header in the application image consisting of metadata about the application; this appears in page zero of the application image, immediately after the interrupt vectors. The bootloader also requires that a hash plus a signature be appended to the image; this data requires 160 bytes.

The bootloader operates by interposing itself between the ST bootloader and the application. When it gets control from the boot loader, it does the following.

- The bootloader image is validated.
- The program flash application image is validated.
- If the application is valid and if no firmware update has been requested, it is launched.
- If a firmware update has been requested, the update image is checked on SPI flash. If valid, and properly signed, the application image is copied to program flash. If successful, the update request is cleared, and the application is launched.
- If the application is invalid, and the update image is invalid, the fallback image is checked. If valid and properly signed, the fallback image is copied to program flash. If successful, the application is launched.  (See [Bootloader States](#bootloader-states) for a more complete discussion.)

The boot sequence runs at 32 MHz; it then restores the system to the post-reset state prior to launching the application.

The bootloader enables the SPI flash, including handling external regulators on boards like the 4801.

The bootloader manipulates the boot LED to indicate lengthy activities and failure modes.

The bootloader does not use the CMSIS include files or the ST HAL; these are large, complex and difficult to review. Instead, the ARM reference manual and STM32L0 SOC manuals were used to prepare simple header files with the required information.

A simple tool, [`mccibootloader_image`][1] is provided for preparing and signing images.

To simplify the development workflow, `mccibootloader_image` works directly on ELF files produced by the linker, and writes ELF files compatible with other tools in the toolchain. The same tool is used for signing bootloader images and signing application images.

For convenience, `mccibootloader_image` reads key-files prepared in OpenSSH format. Thus, `ssh-keygen` can be used used to generate the key files.

In development, a standard "test signing" key is used; this is not secure, but it avoids a special mode in the bootloader to disable signing. (We feel that this makes it less likely that the special mode will accidentally be left on at ship time.)

The bootloader exports a simple API that can be used by applications to communicate with the bootloader and take advantage of the TweetNaCl primitives that are part of the bootloader.

[1]: tools/mccibootloader_image/README.md

### Limitations

Overall, we want to make it difficult for an adversary to inject an untrusted image unless they have physical access to the board. But there are certain issues that we don't address; these may be important to you.

The bootloader does not provide any confidentiality at all for the application images. As the bootloader is intended for open source projects, we don't feel that this is a problem.

The bootloader does not prevent someone with physical access to a device from putting arbitrary software in that device. It cannot; an STLINK can always be used and the device reset to factory.

The bootloader does not check signatures of the application before launching it. It considers a valid SHA512 hash to be to good enough authority to launch the app, because it considers that the app would not be in the flash unless its signature had been verified. Remote code execution could take advantage of this to modify the application maliciously, and then update the hash.

If an adversary can force a remote code execution attack, the bootloader can probably be compromised; but remote code execution also effectively takes over the system, unless the MPU is used; and that's much more intrusive. We feel that should be at a layer above the bootloader.

Signature checks are slow -- about 10 seconds on an STM32L0 at 32 MHz. This is acceptable in MCCI's use cases, as it only happens during a firmware update.

Although coded for portability, the initial release of the bootloader is specific to the STM32L0. The biggest limitation that we're aware of is in the build system, which is not yet prepared for multiple targets.

## MCCI / STM32L0 Deployment Details

This section describes how MCCI deploys the boot loader in our MCCI Catena&reg; products based on the Murata ABZ module.

The boot loader occupies up to 20k of flash, starting at the base of the flash region.

- The STM32 on-chip boot loader requires that the vector table be at the beginning of flash, so it makes more sense for the boot loader to be entirely at the beginning of flash.
- The bootloader actually take less than 0x3000 bytes, so it could fit in 12k bytes, leaving more flash for applications. We reserve 20k on MCCI systems both for future-proofing and to allow enhanced bootloaders with debugging, in-built serial download, and so forth.

On the STM32L0, after programming, MCCI marks the boot loader's memory region as write-protected by default, by setting `FLASH_WRPROT1` bits 0..4 (as appropriate for the actual size of the bootloader). This protects the bootloader against erasure by anything except mass erase.

The boot loader also references the MCCI manufacturing data sector, which is the 4k-byte sector located at the top of the flash region. (The manufacturing data sector is defined by the header file `Catena_FlashParam.h` in Catena-Arduino-Platform. A sector is used because that's the write-protect granularity. `FLASH_WRPROT2` bit 15 is normally set to protect this sector from erasure or accidental modification.)

Memory layout:

|   Base     |      Top     | Size | Contents
:-----------:|:------------:|:----:|---------
`0x08000000` | `0x08004FFF` |  20k | Boot loader
`0x08005000` | `0x0802EFFF` | 168k | Application image
`0x0802F000` | `0x0802FFFF` |   4k | MCCI manufacturing sector; holds serial number, customization, other board details.

### SPI flash layout

We need to arrange data on the SPI flash so that it's easy to set things up, and so that we have a fall-back image.

The partitions we need are shown in the next table.

Name | Base (byte address) | Size (bytes) | Description
-----|------|------|-------------
Fallback | `0` | 256k | The fallback image partition
Update | `0x40000` | 256k | The update image partition
User | `0x80000` | 512k | User space -- can be formatted as a file system, etc.

This layout allows for the fallback image to be write-protected in the SPI flash if desired. Standard SPI flash is write-protected with power-of-two granularity; 256k is the smallest size that allows for the full 168k program space to be used.

### Bootloader RAM layout

The bootloader RAM has the following layout:

- Initialized ram data and executable code initialized by the startup sequence
- BSS Variables
- 4k buffer for reading from SPI flash
- Stack

The STM32L082 has 20k of RAM; we put our variables at the top. Here's a breakdown.

|     Base     |      Top     | Size | Contents
|:------------:|:------------:|:----:|---------
| `0x20000000` | `0x20002FFF` | 12k  | Unused and undisturbed by bootloader.
| `0x20003000` | `0x20004134` | ~4k  | RAM variables, buffers, and code that must be executed from RAM.
| `0x20004134` | `0x20004FFF` | ~4k  | Stack.

### EEPROM usage

The EEPROM has the following contents

- Update request cell

The update request cell is a 32-bit value which must be all ones (0xFFFFFFFF) to be recognized as an update request. The value 0x00000000 is recognized as a clean "no-update" value; all other values are reset to zero, and treated as "no update". As with RAM, we position our 4 bytes at the top of EEPROM. If you add more cells, you'll have to adjust the linker script.

|     Base     |      Top     |   Size  | Contents
|:------------:|:------------:|:-------:|---------
| `0x08080000` | `0x080817FB` | 6k - 4  | Unused and undisturbed by bootloader.
| `0x080817FC` | `0x080817FF` | 4       | The update request cell.

### Abstraction Layer

The following abstract drivers are provided by the platform:

- System drivers, including initialization, deinitialization, failure handling, and delay handling.
- Update flag driver (implemented by EEPROM access)
- The storage driver (which in turn uses a SPI driver)
- Annunciator driver (for user interface)
- The system flash driver (for programming and erasing regions)

### Application Image Structure

Boot images always have the following structure (on Cortex M0).

Images are generally 256-byte aligned (once placed at final address).

They begin with the stack pointer and initial entry point.

```c
typedef struct
  {
  uint32_t  stack;  // must be multiple of 4
  uint32_t  entry;  // must be odd, and must be inside
                    // the program flash region.
  } Mcci_CortexAppEntryContents_t;
```

The first 48 `uint32_t`s (192 bytes) of the image are exception handling vectors. (This includes the `Mcci_CortexAppEntryContents_t` structure already described).

The next 64 bytes are reserved for use by the _application information_ structure, `McciBootloader_AppInfo_t`.

The overall image layout is:

| Bytes   | Content | Discussion & Constraints
| --------|---------|-------------------------
| 0..191 | Vectors | Stack must be in RAM segment. PC must be odd and in [targetAddress + 192..targetAddress + imageSize-4]
| 192..255 | AppInfo header | Dedicated header block with details, including imageSize.
| 256..imageSize - 1 | applicationImage | the application image
| imageSize..imageSize+127 | hash + signature | the hash of 0..imageSize, signed.

### AppInfo overview

The bootloader and all application images contain AppInfo blocks at offset 192 through 255 of their images (relative to the base of their vector page).

| Bytes | Name | Content | Discussion
|-------|------|---------|------------
| 0..3  | `magic` |`'MAP0'`, or 0x3050414d | Dedicated value indicating that this is an AppInfo block.
| 4..7  | `size` |  `0x40`  | Size of the AppInfo block.
| 8..11 | `targetAddress` | base address | `0x08000000` for the boot loader, `0x08005000` for application images.
| 12..15 | `imageSize` | size of image in bytes | Does not include hash and signature data.
| 16..19 | `authSize` | `0xC0` | size of authentication info at end of image |
| 20..23 | `version` | version | Semantic version of app. Byte 23 is major version, 22 is minor version, 21 is patch, and 20 (if non-zero) is the pre-release indictor. Note that prior to comparing semantic versions in this format, you must decrement the LSB modulo 256, so that pre-release 0x00 is greater than any non-zero pre-release value.
| 24..31 | `posixTime` |  seconds since epoch | Normal Posix time; expressed as a 64-bit integer to avoid the year 2037 problem.
| 32..47 | `comment` | UTF8 text, zero-padded | A comment, such as the program name.
| 47..63 | `reserved32` | reserved, zero | Reserved for future use.

### Signature block overview

The signature block appears at address `targetAddress` plus `imageSize`.

| Bytes | Name | Content | Discussion
|-------|------|---------|-----------
| 0..31 | `publicKey` | public key | ed25519 public key corresponding to the private key used to sign this image.
| 32..95 | `hash` | hash of image | SHA-512 hash of image from byte 0 through and including the public key
| 96..159 | `signature` | signature of image | TweetNaCl signature of `hash`, with the duplicated `hash` omitted. To verify, form `signature | hash` and then run the signature check.

### Signature Verification

We validate by computing the hash, and checking it. Then we check the hash by applying`crypto_sign_open()` to the signature block. If the hash is properly signed, and the hash matches the hash of the application image, then we trust the image.

For verifying from SPI flash, we use a modified `crypto_hash()` to calculate the hash in chunks:

* First, we use `crypto_hash_begin()` (not part of the original TweetNaCl library) to initialize the 64-byte hash buffer.
* Then we use the existing `crypto_hashblocks()` to evolve the hash value by iteratively applying it to buffers that are multiples of 64-bytes long (e.g. a 4k buffer).
* Finally, we use `crypto_hash_end()` to handle the partial bytes at the end.

The loop looks like this:

1. Initialize hash.
2. For each block in image:
    1. read block into RAM buffer
    2. update hash given previous hash and new block
3. Validate signature, which by quirks reveals the plaintext of the signature block.
4. Compare signed hash to hash of code.

### Programming app image from SPI

The SPI image itself corresponds directly to the bytes to be programmed into program flash. All Elf headers must be stripped; the approved way to prepare this image is to use `objcopy`, as is done in the bootloader `Makefile` to make a `.bin` file, or in the MCCI Arduino `platform.txt` file, to make a `.bin` file. The `objcopy` step is normally done after signing. If directly loading the image via an STLINK, you might also want to create a `.hex` file.

The bootloader follows this procedure to load images from the SPI flash into program flash.

1. The bootloader erases the portion of the program flash application image space that will be used for the new image.
2. For each 4k block in the new image:
    1. The bootloader reads the block of data from SPI flash into RAM.
    2. The bootloader then programs the block to application flash, by dividing the block into "half pages" and programming using a special function that lives in RAM.
3. Finally, the bootloader verifies the application image by running the application check.

### Checking signatures

It takes a little while to verify a ed25519 signature on the STM32L0; so we only check signatures when deciding whether to update the flash, after we've validated the SHA512 hash.

## The bootloader query API on ARMv6-M systems

Applications may need to get information from the bootloader (e.g. the address of the EEPROM flag used for requesting updates). On ARMv6-M systems using Thumb architecture, exception handling is basically a subroutine call, and the exception processor need not do any special work different than what normal C subroutines must do. The bootloader's SVC vector points to a simple subroutine for performing services for the caller. The caller loads register `r0` with the required service code, loads `r1` with a pointer to a dword to an error cell, loads `r2` and `r3` with any additional parameters, and calls the function pointed to by vector [11] in the bootloader's exception table.

The SVC function has the signature:

```c++
typedef void
(McciBootloaderPlatform_ARMv6M_SvcHandlerFn_t)(
    McciBootloaderPlatform_ARMv6M_SvcRq_t code,
    McciBootloaderPlatform_ARMv6M_SvcError_t *pError,
    uint32_t arg1,
    uint32_t arg2
    );
```

`McciBootloaderPlatform_ARMv6M_SvcRq_t` and `McciBootloaderPlatform_ARMv6M_SvcError_t` are defined as enumeration types of size `uint32_t`.

The error code cell will be set to zero for success, and to a non-zero error code for failure. The error code 0xFFFFFFFFu is used as the "catch-all" code if the request code is not recognized. The error code 0xFFFFFFFEu is used for "invalid parameter".

### Get Update-Flag Pointer

The request `McciBootloaderPlatform_ARMv6M_SvcRq_GetUpdatePointer` interprets `arg1` as a pointer to a `uint32_t*` cell, and delivers a pointer to the update flag to that cell. The caller must have a library that enables writing to the EEPROM. The bootloader doesn't try to export its hardware access libraries, because there's no guarantee that the caller has the hardware set up correctly for the bootloader's use.

### Initialize hash buffer

The request `McciBootloaderPlatform_ARMv6M_SvcRq_HashInit` interprets `arg1` as a pointer to a 64-byte hash buffer, and initializes it to the SHA-512 initialization vector.

### Hash blocks

The request `McciBootloaderPlatform_ARMv6M_SvcRq_HashBlocks` computes an intermediate hash on a part of a message. It interprets `arg1` as a pointer to a structure of type `McciBootloaderPlatform_ARMv6M_SvcRq_HashBlocks_Arg_t`.  This structure has the following layout:

```c
typedef struct McciBootloaderPlatform_ARMv6M_SvcRq_HashBlocks_Arg_s {
   void *pHash;                // pointer to the 64-byte hash buffer
   const uint8_t *pMessage;    // pointer to message fragment
   size_t nMessage;            // count of message fragment
} McciBootloaderPlatform_ARMv6M_SvcRq_HashBlocks_Arg_t;
```

The hash buffer at `*pHash` is updated to reflect the data in `pMessage[]`. All fragments in a message except the last should be a multiple of 128 bytes long. `nMessage` is updated to reflect the number of bytes left over (if message is not a multiple of 128 bytes long).

### Finish a hash operation

The request `McciBootloaderPlatform_ARMv6M_SvcRq_HashBlocks` finishes a
hash operation. It interprets `arg1` as a pointer to a structure of type `McciBootloaderPlatform_ARMv6M_SvcRq_HashFinish_Arg_t`. This structure has the following layout:

```c
typedef struct McciBootloaderPlatform_ARMv6M_SvcRq_HashFinish_Arg_s {
   void *pHash;                // pointer to the hash buffer
   const uint8_t *pMessage;    // pointer to remaining bytes of message
   size_t nMessage;            // length of remaining portion of message
   size_t nOverall;            // number of bytes in message, overall
} McciBootloaderPlatform_ARMv6M_SvcRq_HashFinish_Arg_t;
```

## Bootloader States

The following table summarizes the bootloader's decisions.

| Case  |  Bootloader Image | App image  | Update Flag | Update Image | Fallback Image |  Action | Comments
|:-----:|:-----:|:------:|:------:|:-------:|:------:|:------------|--------
|  (1)  |  NG   |   -    |   -    |   -     |  -     |  Halt with indication
|  (2)  |  OK   |   OK   |   "go"  |   -     |  -     |  Launch app
|  (3)  |  OK   |   OK   |  "update" |   NG    |  -     |  Clear flag, launch app
|  (4)  |  OK   |   OK   |  "update" |   OK    |  -     |  Load update image, clear flag & reevaluate. | Power failure during flash will bring us up in some App NG state, but Update Flag will still be "update"
|  (5)  |  OK   |   NG   |  "update" |  OK   |  - | See (4). | This state is hit after a power fail in (4).
|  (6)  |  OK   |   NG   |  "update" |  NG   |  OK | Load fallback image, clear flag, reevaluate. |
|  (7)  |  OK   |   NG   |  "go"    |  -    |  OK    |  Load fallback image, clear flag & and reevaluate | Note that we do not load the update image in this case, even if it looks good, because we have not ben requested to do so.
|  (8)  |  OK   |   NG   |  "go"  |   OK    |  NG    | Load update image, clear flag, reevaluate. | This is the only case in which we'll load the update image when the update flag is not set. The justification is that it allows us to potentially return the system to a working state.
|  (9)  |  OK   |   NG   |   -    |   NG    |  NG    |  Clear flag, halt with indication

The implementation matrix is a little crazy because it's expensive to evaluate quality of update and fallback images.

## Practical Details

### SPI flash initialization

The manufacturing process may need to initialize the fallback image on the flash. This is different for mass product compared to "Arduino developers". We anticipate that Arduino developers will initially leave the fallback image blank; hence row 8 in the table above may get used a lot.

Manufacturing will need tools for loading the fallback image and setting the write-protect bit.

The fallback image could be small, in which case a user could save SPI flash room by rearranging the partition boundaries. However, we don't plan to support that, at least at first.

### Generating public/private key pairs

We recommend using `ssh-keygen` to generate keys. Please see [`mccibootloader_image` documentation](tools/mccibootloader_image/README.md#generating-a-key-pair) for complete instructions.

The bootloader should be hashed and signed by `mccibootloader_image`; the signing process also sets the public key to be used by the bootloader for verifying images.

### Building

Install GNU Make if not present (on Windows, use [scoop](https://scoop.io)).

If on Windows, install git bash.

Install Arduino IDE for target.

If you don't already have the bootloader image tool installed, you'll need to build it first. Change directory to `tools/mccibootloader_image` and following the instructions to build the image tool (if not already built).

Find the compiler directory and prefix for the target. The Arduino forum explains how this is done, see for example [this post](https://forum.arduino.cc/index.php?topic=616372.0).

Quick summary: turn on verbose output, do a build of any sketch with your target selected, and look at the log. The compiler path will be at the start of each command, for example as:

<code><i>c:\Users\example\AppData\Local\arduino15\packages\mcci\tools\arm-none-eabi-gcc\6-2017-q2-update\bin\arm-none-eabi-</i><b>gcc</b> ...</code>

Grab all the stuff before the "`gcc`", including the trailing dash.

Do a build, setting `CROSS_COMPILE` to point to the compiler directory and tool prefix, like this.

```bash
CROSS_COMPILE='compiler_path_and_prefix' make
```

#### Windows Build Example

```bash
CROSS_COMPILE='c:\Users\example\AppData\Local\arduino15\packages\mcci\tools\arm-none-eabi-gcc\6-2017-q2-update\bin\arm-none-eabi-' make
```

If you prefer, you can use forward slashes and `~`-notation for your home directory, like this:

```bash
CROSS_COMPILE=~/AppData/Local/arduino15/packages/mcci/tools/arm-none-eabi-gcc/6-2017-q2-update/bin/arm-none-eabi- make
```

### Installing the bootloader

Use ST-LINK and download using the -bin option after signing, using address 0x08000000:

```bash
st-flash --format binary bootloader-image.bin 0x08000000
```

Or use gdb and the load command.

1. Start a command window.
2. Start the gdb server:

    ```bash
    st-util --port 1234
    ```

3. Start a second command window.
4. Launch gdb using the elf file:

    ```bash
    ~/AppData/Local/arduino15/packages/mcci/tools/arm-none-eabi-gcc/6-2017-q2-update/bin/arm-none-eabi-gdb McciBootloader_4801.elf
    ```

5. In gdb, enter the following command to connect:

    ```console
    (gdb) target extended-remote :1234
    ```

6. Download the code:

    ```console
    (gdb) load
    ```

### STM32L0 Watchdog timer

The STM32L0 has a watchdog timer that can be enabled in hardware by the option bytes. The bootloader currently does not update the watchdog timer(s) although it is architected to be able to do it.

## Meta

### License

The bootloader and top-level wrappers are released under the [MIT license](./LICENSE). Commercial licenses and commercial support are available from MCCI Corporation. The TweetNaCl and NaCl code is all public domain (including MCCI contributions in those directories). The collective work is MIT licensed.

### Support Open Source Hardware and Software

MCCI invests time and resources providing this open source code, please support MCCI and open-source hardware by purchasing products from MCCI, Adafruit and other open-source hardware/software vendors!

For information about MCCI's products, please visit [store.mcci.com](https://store.mcci.com/).

### Trademarks

MCCI and MCCI Catena are registered trademarks of MCCI Corporation. All other marks are the property of their respective owners.
