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

The boot loader the occupies 12k of flash, starting at the base of the flash region (locations 0x08000000 through 0x080027FF). The STM32 on-chip bootloader requires that the vector table be at the beginning of flash, so we

On the STM30L0, after programming, MCCI marks the boot loader's memory region as write-protected by default, by setting `FLASH_WRPOT1` bits 0, 1, and 2. In addition. This protects the bootloader against erasure by anything except mass erase.

The boot loader also references the MCCI manufacturing data sector, which is located at the top of the flash region.
