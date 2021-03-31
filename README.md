# MCCI STM32L0 Bootloader

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
- [Technical Discussion](#technical-discussion)
	- [SPI flash layout](#spi-flash-layout)
	- [Bootloader RAM layout](#bootloader-ram-layout)
	- [Abstraction Layer](#abstraction-layer)
	- [Application Image Structure](#application-image-structure)
	- [AppInfo overview](#appinfo-overview)
	- [Signature Verification](#signature-verification)
	- [Programming app image from SPI](#programming-app-image-from-spi)
	- [Invariants that the bootloader must maintain](#invariants-that-the-bootloader-must-maintain)
	- [SPI flash initialization](#spi-flash-initialization)
- [Practical Details](#practical-details)
	- [Generating public/private key pairs](#generating-publicprivate-key-pairs)
	- [Building](#building)
	- [Installing the bootloader](#installing-the-bootloader)
- [Meta](#meta)
	- [License](#license)
	- [Support Open Source Hardware and Software](#support-open-source-hardware-and-software)
	- [Trademarks](#trademarks)

<!-- /TOC -->
<!-- markdownlint-restore -->
<!-- Due to a bug in Markdown TOC, the table is formatted incorrectly if tab indentation is set other than 4. Due to another bug, this comment must be *after* the TOC entry. -->

## Introduction

The MCCI&reg; STM32L0 bootloader gets control from the ST boot loader, and handles various administrative tasks prior to transferring control to the application program.

- The program flash application image is validated.
- If the application is valid and if no firmware update has been requested, it is launched.
- If a firmware update has been requested, the update image is checked on SPI flash. If valid, and properly signed, the application image is copied to program flash. If successful, the update request is cleared, and the application is launched.
- If the application is invalid, and the update image is invalid, the fallback image is checked. If valid and properly signed, the fallback image is copied to program flash. If successful, the application is launched.

During the boot sequence, the watchdog is kept up to date (if enabled), etc.

The boot sequence runs at the 32 MHz clock rate.

The bootloader enables the SPI flash, including handling external regulators on boards like the 4801.

The bootloader manipulates the boot LED to indicate lengthy activities and failure modes.

The bootloader does not use the CMSIS include files or the ST HAL; these are large, complex and difficult to review. Instead, the ARM reference manual and STM32L0 SOC manuals were used to prepare simple header files with the required information.

## Technical Discussion

The boot loader is coded for clarity and ease of understanding and review. The bootloader manages firmware update from SPI flash; it is the application's job to get the data into the SPI flash. No conditional compiles are used in the C files. The bootloader supplies its own link script. A "platform interface" structure separates the business logic of the bootloader from the low-level hardware-dependent functions.

Hashing and signature-verification functions are provided by the "TweetNaCl" library, via the "MCCI TweetNaCl" library.

The overall goal for review is to make the bootloader's operations *explicit* rather than depending on *implicit* behavior. For example, the bootloader does not use the normal C runtime startup, but is rather invoked directly from the reset vector of the bootloader. The bootloader and the linker script cooperate so that RAM variables (and RAM-based code) get initialized very early in the boot.

The boot loader the occupies up to 20k of flash, starting at the base of the flash region. The STM32 on-chip bootloader requires that the vector table be at the beginning of flash, so it makes more sense for the boot loader to be entirely at the beginning of flash.

On the STM32L0, after programming, MCCI marks the boot loader's memory region as write-protected by default, by setting `FLASH_WRPROT1` bits 0..4 (as appropriate for the actual size of the bootloader). This protects the bootloader against erasure by anything except mass erase.

The boot loader also references the MCCI manufacturing data sector, which is the 4k-byte sector located at the top of the flash region. (The manufacturing data sector is defined by the header file `Catena_FlashParam.h` in Catena-Arduino-Platform. A sector is used because that's the write-protect granularity. `FLASH_WRPROT2` bit 15 is normally set to protect this sector from erasure or accidental modification.)

To summarize:

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

The EEPROM has the following contents

- Update request cell

The update request cell is a 32-bit value which must be all ones (0xFFFFFFFF) to be recognized as an update request. The value 0x00000000 is recognized as a clean "no-update" value; all other values are reset to zero, and treated as "no update".

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

The first 48 dwords (192 bytes) (including the above two dwords) of the image are exception handling vectors.

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
| 16..19 | `authSize` | `0x80` | size of authentication info at end of image |
| 20..23 | `version` | version | Semantic version of app. Byte 23 is major version, 22 is minor version, 21 is patch, and 20 (if non-zero) is the pre-release indictor. Note that prior to comparing semantic versions in this format, you must decrement the LSB modulo 256, so that pre-release 0x00 is greater than any non-zero pre-release value.
| 24..31 | `posixTime` |  seconds since epoch | Normal Posix time; expressed as a 64-bit integer to avoid the year 2037 problem.
| 32..63 | `publicKey` | public key | ed25519 public key corresponding to the private key used to sign this image.

### Signature Verification

We validate by computing the hash, and checking it. Then we check the hash by `crypto_sign_open()` to the signature block, disclosing the signed hash. If the hash is properly signed, and the hash matches the hash of the application image, then we trust the image.

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

Once the program image has been approved, we follow this procedure to load it into flash.

1. Erase program flash application image space
2. For each block in image:
    1. Read the block of data from SPI flash
    2. Program block by dividing it into "half pages" and programming using a special function that lives in RAM.
3. Finally, verify the application image by running the application check.

### Invariants that the bootloader must maintain

It takes a long time to verify a ed25519 signature on the STM32L0;
so we only check signatures when deciding whether to update
the flash. Otherwise we check the SHA512. The program format
still includes the signature, but we only check this when
deciding whether to apply it to the flash.

The following table summarizes the bootloader's decisions.

| Case  |  Bootloader Image | App image  | Update Flag | Update Image | Fallback Image |  Action | Comments
|:-----:|:-----:|:------:|:------:|:-------:|:------:|:------------|--------
|  (1)  |  NG   |   -    |   -    |   -     |  -     |  Halt with indication
|  (2)  |  OK   |   OK   |   "go"  |   -     |  -     |  Launch app
|  (3)  |  OK   |   OK   |  "update" |   NG    |  -     |  Launch app, clear flag
|  (4)  |  OK   |   OK   |  "update" |   OK    |  -     |  Load update image, clear flag & reevaluate. | Power failure during flash will bring us up in some App NG state, but Update Flag will still be "update"
|  (5)  |  OK   |   NG   |  "update" |  OK   |  - | See (4). | This state is hit after a power fail in (4).
|  (6)  |  OK   |   NG   |  "update" |  NG   |  OK | Load fallback image, clear flag, reevaluate. |
|  (7)  |  OK   |   NG   |  "go"    |  -    |  OK    |  Load fallback image, clear flag & and reevaluate | Note that we do not load the update image in this case, even if it looks good, because we have not ben requested to do so.
|  (8)  |  OK   |   NG   |  "go"  |   OK    |  NG    | Load update image, clear flag, reevaluate. | This is the only case in which we'll load the update image when the update flag is not set.
|  (9)  |  OK   |   NG   |   -    |   NG    |  NG    |  Halt with indication

The implementation matrix is a little crazy because it's expensive to evaluate quality of update and fallback images.

### SPI flash initialization

The manufacturing process may need to initialize the fallback image on the flash. This is different for mass product compared to "Arduino developers". We anticipate that Arduino developers will initially leave the fallback image blank; hence row 8 in the table above may get used a lot.

Manufacturing will need tools for loading the fallback image and setting the write-protect bit.

The fallback image could be small, in which case a user could save SPI flash room by rearranging the partition boundaries. However, we don't plan to support that, at least at first.

## Practical Details

### Generating public/private key pairs

We recommend using `ssh-keygen` to generate keys. Please see [`mccibootloader_image` documentation](tools/mccibootloader_image/README.md#generating-a-key-pair) for complete instructions.

The bootloader should be hashed and signed by `mccibootloader_image`; the signing process also sets the public key to be used by the bootloader for verifying images.

### Building

Install GNU Make if not present (on Windows, use [scoop](https://scoop.io)).

Install Arduino IDE for target.

Do a build, setting CROSS_COMPILE to point to the compile directory, like this.

```bash
CROSS_COMPILE=~/AppData/Local/arduino15/packages/mcci/tools/arm-none-eabi-gcc/6-2017-q2-update/bin/arm-none-eabi- make
```

Change directory to `tools/mccibootloader_image` and build the image tool (if not already built).

### Installing the bootloader

Use ST-LINK and download using the -bin option after signing, using address 0x08000000:

```bash
st-flash --format binary bootloader-image.bin 0x08000000
```

## Meta

### License

The bootloader and top-level wrappers are released under the [MIT license](./LICENSE). Commercial licenses and commercial support are available from MCCI Corporation. The TweetNaCl and NaCl code is all public domain (including MCCI contributions in those directories). The collective work is MIT licensed.

### Support Open Source Hardware and Software

MCCI invests time and resources providing this open source code, please support MCCI and open-source hardware by purchasing products from MCCI, Adafruit and other open-source hardware/software vendors!

For information about MCCI's products, please visit [store.mcci.com](https://store.mcci.com/).

### Trademarks

MCCI and MCCI Catena are registered trademarks of MCCI Corporation. All other marks are the property of their respective owners.
