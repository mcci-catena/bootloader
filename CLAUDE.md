# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

MCCI Trusted Bootloader for STM32L0 -- a security-focused bootloader for IoT devices using ed25519 signatures and SHA-512 hashing (via TweetNaCl). Targets ARM Cortex-M0+ (STM32L0). Licensed GPLv2.

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

Output lands in `build/arm-none-eabi/release/` -- produces `.elf`, `.bin`, and `.hex` for each bootloader variant (McciBootloader_4801, McciBootloader_46xx).

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
platform/soc/stm32l0/         STM32L0 SoC drivers (flash, system init)
platform/board/mcci/
  catena_abz/                 Base board (vectors, SPI, storage, EEPROM, annunciator)
  catena4801/                 4801 variant (platform interface, storage init)
  catena46xx/                 46xx variant (platform interface, storage init)
platform/driver/
  flash_mx25v8035f/           SPI flash driver
```

Each layer builds as a separate static library. Board-specific libraries provide the concrete `McciBootloaderPlatform_Interface_t` instance.

### Build system structure

The Makefile uses `mk/setup.mk` (compiler/flags) and `mk/tail.mk` (rule generation via `MCCI_DOCOMPILE`, `MCCI_DOLIBRARY`, `MCCI_DO_BOOTLOADER` macros). Adding a new board variant means adding a new `BOOTLOADERS +=` entry, its `LIBS_*` and `LDSCRIPT_*` variables, and a board-specific library.

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

Register definitions come directly from ARM and STM32L0 reference manuals, in simple header files under `platform/soc/stm32l0/i/`.

### Compiler flags

`-Wall -Werror -Werror=missing-prototypes -std=gnu11 -nostdlib -mcpu=cortex-m0plus -mthumb`. Optimization is `-Os` for bootloader code, `-O2` for TweetNaCl.

## Memory Layout (STM32L0)

| Region | Address | Size |
|---|---|---|
| Bootloader | 0x08000000-0x08004FFF | 20k |
| Application | 0x08005000-0x0802EFFF | 168k |
| Manufacturing | 0x0802F000-0x0802FFFF | 4k |

SPI flash: fallback image at 0x0, update image at 0x40000, user storage at 0x80000.
