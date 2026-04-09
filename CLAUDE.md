# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

MCCI Trusted Bootloader -- a security-focused bootloader for IoT devices using ed25519 signatures and SHA-512 hashing (via TweetNaCl). Targets ARM Cortex-M0+ (STM32L0) and Cortex-M7 (STM32H7). Licensed GPLv2.

## Build Commands

### Prerequisites

- ARM cross-compiler (`arm-none-eabi-gcc`), typically from Arduino MCCI Catena STM32 board package
- GNU Make
- Git bash on Windows

### Building the bootloader

```bash
# Set CROSS_COMPILE to your arm-none-eabi- toolchain prefix
CROSS_COMPILE=/path/to/arm-none-eabi- make
```

Output lands in `build/arm-none-eabi/release/` -- produces `.elf`, `.bin`, and `.hex` for each bootloader variant (McciBootloader_4801, McciBootloader_46xx, McciBootloader_stm32h7b3i_dk).

The top-level `Makefile` builds all targets. Per-family makefiles are also available:

```bash
# Build only STM32L0 targets
CROSS_COMPILE=/path/to/arm-none-eabi- make -f Makefile-stm32l0.mk

# Build only STM32H7 targets
CROSS_COMPILE=/path/to/arm-none-eabi- make -f Makefile-stm32h7.mk
```

Per-family builds use a family-qualified output directory (e.g., `build/stm32l0-arm-none-eabi/release/`).

### Building the image signing tool (host, no cross-compiler)

```bash
cd tools/mccibootloader_image
make
```

### Clean

```bash
make clean
```

### Debug build

```bash
CROSS_COMPILE=/path/to/arm-none-eabi- BUILDTYPE=debug make
```

### Verbose make output

```bash
MAKEVERBOSE=1 CROSS_COMPILE=... make
```

### Signing a bootloader image

```bash
mccibootloader_image INPUT OUTPUT --sign --add-time --keyfile path/to/key.pem
```

Test signing key: `tools/mccibootloader_image/test/mcci-test.pem`

### Installing to hardware

```bash
st-flash --format binary build/arm-none-eabi/release/McciBootloader_4801.bin 0x08000000
```

## Architecture

### Platform abstraction via function pointers

The core bootloader logic (`src/`) is hardware-independent. All hardware access goes through `McciBootloaderPlatform_Interface_t` (defined in `platform/i/mcci_bootloader_platform.h`), a struct of function pointers for system init, flash operations, SPI, storage, and LED annunciation. No conditional compilation in C files -- platform differences are handled entirely through this interface.

### Layer hierarchy

```
src/                          Portable bootloader logic (state machine, image validation)
platform/src/                 Platform entry/fail handlers
platform/arch/cm0plus/        ARM Cortex-M0+ specific (image validation, app launch)
platform/arch/cm7/            ARM Cortex-M7 specific (image validation, app launch)
platform/soc/stm32l0/         STM32L0 SoC drivers (flash, system init)
platform/soc/stm32h7/         STM32H7 SoC drivers (flash, system init)
platform/board/mcci/
  catena_abz/                 Base board for Murata ABZ (vectors, SPI2, storage, EEPROM, annunciator)
  catena4801/                 4801 variant (platform interface, storage init)
  catena46xx/                 46xx variant (platform interface, storage init)
  module/
    murata-1sj/               Murata 1SJ module hardware definition (planned)
    mcci-model5082/           MCCI Model 5082 module hardware definition (planned)
  catena_1sj/                 Board base for Murata 1SJ (calls module/murata-1sj) (planned)
  catena52xx/                 5210/5220 variant (planned)
  catena5230/                 5230 variant with NPM1300 PMIC (planned)
  catena_5082/                Board base for Model 5082 (calls module/mcci-model5082) (planned)
  catena51xx/                 5120 variant (planned)
platform/board/st/
  stm32h7b3i_dk/              ST Discovery Kit (vectors, annunciator, platform interface)
platform/driver/
  flash_mx25v8035f/           SPI flash driver (all STM32L0 boards, works with MX25R series too)
```

Each layer builds as a separate static library. Board-specific libraries provide the concrete `McciBootloaderPlatform_Interface_t` instance.

### Build system structure

The build system is modular: each board's bootloader `.mk` file (e.g., `mcci_bootloader_4801.mk`) includes its own library dependencies transitively. The top-level `Makefile` just includes `mk/setup.mk`, the bootloader `.mk` files, and `mk/tail.mk`. Per-family makefiles (`Makefile-stm32l0.mk`, `Makefile-stm32h7.mk`) set `TARGET_FAMILY` and include only the relevant board(s).

`mk/setup.mk` handles compiler/flags, `mk/tail.mk` handles rule generation via `MCCI_DOCOMPILE`, `MCCI_DOLIBRARY`, `MCCI_DO_BOOTLOADER` macros. Adding a new board variant means creating a bootloader `.mk` that sets `BOOTLOADERS +=`, `LIBS_*`, `LDSCRIPT_*`, and includes its library `.mk` file. The library `.mk` files use include guards and pull in their own prerequisites.

The tools subdirectory has its own parallel build system: `tools/mk/tool_setup.mk` and `tools/mk/tool_tail.mk`.

### Bootloader state machine

Entry point: `McciBootloader_main()` in `src/mccibootloader_main.c`. Implements a 9-state decision tree covering: primary app valid, fallback available, update image present, and power-failure recovery during flash programming.

### Image format

Applications must include a 64-byte `McciBootloader_AppInfo_t` struct immediately after the vector table, plus 160 bytes of authentication data (hash + signature) appended to the image. The AppInfo offset depends on the target architecture: 0xC0 (192) for Cortex-M0/M0+ (48 vectors), 0x3C0 (960) for Cortex-M7 with 240 vectors, 0x400 (1024) for Cortex-M7 with 256 vectors. The `mccibootloader_image` tool probes all three offsets automatically.

### Git submodules

- `pkgsrc/mcci_tweetnacl` -- TweetNaCl crypto library (unmodified)
- `pkgsrc/mcci_arduino_development_kit_adk` -- MCCI ADK (type definitions, macros)

Clone with `--recursive` or run `git submodule update --init`.

## Code Conventions

### Naming

- Types: `McciBootloader*_t` (typedef), `McciBootloader*_s` (struct tag), `McciBootloader*_e` (enum tag)
- Functions: `McciBootloader_VerbNoun()` or `McciBootloaderPlatform_VerbNoun()`
- Function pointer types: `*_Fn_t` suffix
- Constants/enums: `McciBootloaderError_OK`, `McciBootloaderState_stCheckPrimaryApp`, etc.

### File headers

Every file has a standard header block with Module, Function, Copyright, Author fields. Copyright is MCCI Corporation.

### No CMSIS or ST HAL

Register definitions come directly from ARM and STM32 reference manuals, in simple header files under `platform/arch/*/i/` (ARM core registers) and `platform/soc/*/i/` (SoC peripheral registers).

### Compiler flags

Common: `-Wall -Werror -Werror=missing-prototypes -std=gnu11 -nostdlib -mthumb`. CPU-specific flags are set per architecture: `-mcpu=cortex-m0plus` (STM32L0) or `-mcpu=cortex-m7` (STM32H7). Optimization is `-Os` for bootloader code, `-O2` for TweetNaCl.

## Memory Layout (STM32L0)

| Region | Address | Size |
|---|---|---|
| Bootloader | 0x08000000-0x08004FFF | 20k |
| Application | 0x08005000-0x0802EFFF | 168k |
| Manufacturing | 0x0802F000-0x0802FFFF | 4k |

SPI flash: fallback image at 0x0, update image at 0x40000, user storage at 0x80000.

## Planned: Catena 51xx and 52xx Support

See `doc/plan-catena-51xx-52xx-bootloader-support.md` for the full implementation plan. Key facts:

- **52xx** (Murata 1SJ, STM32L072): SPI flash on SPI1 (PA4-PA7), LED on PB2 (same as ABZ). 5230 has NPM1300 PMIC on I2C2 (PB10/PB11, addr 0x6B) controlling flash power via LOADSW2.
- **51xx** (Model 5082, STM32L082): SPI flash on SPI2 (PB12-PB15, same as ABZ), LED on PB5. No PMIC.
- New targets: `McciBootloader_52xx`, `McciBootloader_5230`, `McciBootloader_51xx`.
- Existing `flash_mx25v8035f` driver works unchanged with MX25R-series flash parts.
- Same STM32L0 memory layout and SPI flash storage addresses as existing boards.

## Memory Layout (STM32H7 -- stm32h7b3i_dk)

| Region | Address | Size |
|---|---|---|
| Bootloader | 0x08000000-0x08007FFF | 32k |
| Update request | 0x08008000-0x08009FFF | 8k |
| Manufacturing | 0x0800A000-0x0800BFFF | 8k |
| Application | 0x08010000-0x0808FFFF | 512k |
| OTP | 0x08FFF000-0x08FFF3FF | 1k |

RAM: working RAM and stack are allocated from the top of AHB SRAM (0x30000000, 128k).
