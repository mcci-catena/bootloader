# MCCI STM32L0 Bootloader

## Introduction

The MCCI&reg; STM32L0 bootloader gets control from the ST boot loader, and handles various administrative tasks prior to transferring control to the application program.

- The application image is validated.
- SPI flash is checked for a pending image that is more up-to-date than the current image.
- If indicated, the pending image from SPI flash is copied to program flash.
- The resulting image is re-validated.
- Control is transferred to the application.

During the boot sequence, the watchdog is kept up to date (if enabled), etc.

It runs at the default post-boot clock rate.

It enables the SPI flash, including handling external regulators.

It manipulates the boot LED to indicate lengthy activities and failure modes.

Although the bootloader makes use of CMSIS header files from the MCCI BSP, this bootloader does not use the ST HAL.

The SPI flash and external regulators are accessed with platform-specific functions. Libraries are provided for the various components used in MCCI Catena boards.

### Comparison to other boot loaders

The boot loader uses on-the-iron C techniques -- no assumptions are made about initialization -- initialized variables must be `const`; all read/write variables must be uninitialized.

The STM32L0 variant depends on the ST bootloader for DFU and other dynamic download support. Unlike other boot loaders, no attempt is made to enable USB or other features of the device.

Unlike many other bootloaders, this module attempts to completely control its environment, so far as the compiler and linker allow. Therefore, we supply our own link script, which does exactly and only what the bootloader wants; and the bootloader expects boot-loader-specific symbols to be exported by the linker.

The goal is to make the bootloader's operations *explicit* rather than depending on *implicit* behavior.

One example of this: the bootloader does not use the normal C runtime startup. This means that the bootloader is responsible for initializing RAM, etc.; it means in turn that the bootloader does not, by default, support initialization of data variables. (To enforce that, the default linker script will display an error if ordinary initialized data is found in the bootloader image.)

## Memory mapping and image layout

The boot loader the occupies 12k of flash, starting at the base of the flash region (locations 0x08000000 through 0x080027FF). The STM32 on-chip bootloader requires that the vector table be at the beginning of flash, so it makes more sense for the boot loader to be entirely at the beginning of flash.

On the STM32L0, after programming, MCCI marks the boot loader's memory region as write-protected by default, by setting `FLASH_WRPROT1` bits 0, 1, and 2. This protects the bootloader against erasure by anything except mass erase.

The boot loader also references the MCCI manufacturing data sector, which is the 4k-byte sector located at the top of the flash region. (The manufacturing data sector is defined by the header file Catena_FlashParam.h in Catena-Arduino-Platform. A sector is used because that's the write-protect granularity. `FLASH_WRPROT2` bit 15 is normally set to protect this sector from erasure or accidental modification.)

To summarize:

|       Base |      Top     | Size | Contents
:-----------:|:------------:|:----:|---------
`0x08000000` | `0x08002FFF` |  12k | Boot loader
`0x08003000` | `0x0802EFFF` | 176k | Application image
`0x0802F000` | `0x0802FFFF` |   4k | MCCI manufacturing sector; holds serial number, customization, other board details. Could hold public key for board and public key for MCCI if we want to do code signing.

## Signature Verification

1. Initialize signature checker with public key
2. For each block in image:
    1. read block into RAM buffer
    2. update signature given previous signature and new block
3. Finally, validate signature.

We could build Arduino wrappers to test this (or test on Linux quickly), provided we have a signed test image living in SPI flash. Recommended test sequence.

1. create a signed test image (and possibly prototype signing tools)
2. build a PC-based test that verifies the signed image
3. copy signed image to SPI flash using Arduino sketch copies from serial command port and then checks signature
4. port code that reads and checks into bootloader.

## Programming app image from SPI

1. Erase application image space
2. For each block in image
    1. Read block of data from SPI flash
    2. Program block by dividing into half pages and calling the HAL program routine (or a copy of the HAL program routine that we put in the boot loader; it's pretty small, and it might be better to control it).
3. Verify image by running CRC32 check -- there's hardware CRC32.

## SPI flash layout

We need to arrange data on the SPI flash so that it's easy to set things up, and so that we have a fall-back image.

For flexibility we could have a small table; or we could just use fixed partitions.

The partitions we need are:

Name | Size | Description
-----|------|-------------
Meta | 1k   | Metadata about SPI flash including real locations of App1 and App2, and sizes of all three flash partitions.
Recovery | 172k | The image to use for recovery, in case program flash is corrupt and neither app image is OK. This can be write-protected at the factory.
App1 | 172k | App image 1
App2 | 172k | App image 2
User | 504k | User space -- can be formatted as a file system, etc.

The reason for making this table driven is that if the boot loader has to grow, the app image size max will change.

## Invariants that the bootloader must maintain

Program flash is equal to the most valid image of { Program Flash, Recovery, App1, App2 }.

Checking validity:

Image | How to check
------|---------------
Program Flash | Use CRC32 hardware from STM32
Recovery | Run signature check
App1 | Run signature check
App2 | Run signature check

Fallback (EEPROM) | Update Request (in EEPROM) | Program Flash | Recovery | App1 | App2 | Action
------------------|---------------------------|---------------|----------|------|------|--------
x | No | Valid | x | x | x | Jump to program flash.
x | A1 | x | x | Yes | x | Load App1, reset update, set fallback to A1, go.
x | A1 | Invalid | Yes | No | x | Load recovery, reset update, set fallback to R, go.
x | A1 | Invalid | No | No | x | App1 and recovery no good, loop flashing lights.
x | A2 | x | x | x | Yes | Load App2, reset EEPROM, set fallback to A2, go.
x | A1 | Invalid | x | x | Yes | Treat as recovery case.
x | R | x | Yes | x | x | Load recovery, reset EEPROM, set fallback to R, go.
R | No | Invalid | Yes | x | x | Load recovery, go.
R | No | Invalid | No | x | x | Recovery is no good; loop flashing lights.
A1 | No | Invalid | x | Yes | x | Load APP1, go
A1 | No | Invalid | Yes | No | x | Load recovery, set fallback to R, go.
A1 | No | Invalid | No | No | x | App1 and recovery no good, loop flashing lights.
A2 | No | Invalid | x | Yes | x | Load APP1, go
A2 | No | Invalid | Yes | x | Yes | Load recovery, set fallback to R, go.
A2 | No | Invalid | No | x | No | App2 and recovery no good, loop flashing lights.

## SPI flash initialization

The manufacturing process will have to initialize the SPI flash metadata.

We will need tools for loading the recovery image and setting the write-protect bit.

The recovery image could be small, in which case we could save room by making it smaller. The recovery image should at least flash the LED in a distinctive pattern.
