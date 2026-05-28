# Plan: Add Catena 51xx and 52xx Bootloader Support

*Note*: this plan is out of date in several sections. We will review and converge this in our next work session.

## Context

The MCCI Trusted Bootloader currently supports Catena 46xx and 4801 boards (Murata ABZ / STM32L0). Two new product families need bootloader support:

- **Catena 52xx** (Murata 1SJ module, STM32L072 + SX1262): 5210/5220 (simple) and 5230 (NPM1300 PMIC for power management)
- **Catena 51xx** (MCCI Model 5082 module, STM32L082): 5120 with external LoRa module

The key hardware differences from existing boards are:
- 52xx uses **SPI1 on PA4-PA7** for flash (ABZ uses SPI2 on PB12-PB15), but LED is **PB2** (same as ABZ)
- 51xx uses **SPI2 on PB12-PB15** for flash (same as ABZ), but LED is **PB5** (ABZ uses PB2)
- 5230 has an NPM1300 PMIC on I2C2 (PB10/PB11, addr 0x6B) that must enable LOADSW2 to power the SPI flash, then disable it before app launch for micropower

## Hardware Pin Summary

| Signal | ABZ (46xx/4801) | 1SJ (52xx) | 5082 (51xx) |
|--------|----------------|------------|-------------|
| SPI peripheral | SPI2 (APB1) | SPI1 (APB2) | SPI2 (APB1) |
| NSS | PB12 (AF0) | PA4 (AF0) | PB12 (AF0) |
| SCK | PB13 (AF0) | PA5 (AF0) | PB13 (AF0) |
| MISO | PB14 (AF0) | PA6 (AF0) | PB14 (AF0) |
| MOSI | PB15 (AF0) | PA7 (AF0) | PB15 (AF0) |
| LED | PB2 | PB2 | PB5 |
| I2C1 SCL/SDA | PB8/PB9 | PB8/PB9 | PB8/PB9 |
| I2C2 SCL/SDA | -- | PB10/PB11 (5230) | -- |
| Flash chip | MX25V8035F (1MB) | MX25R1635F (2MB) | MX25R8035F (1MB) |
| PMIC | none | NPM1300 @ 0x6B (5230) | none |

## Module vs. Board Layering

A **module** (`module/murata-1sj`, `module/mcci-model5082`) defines what the hardware IS: pin assignments, peripheral selections, available interfaces. These are header-only -- no `.c` files, just macros and constants describing the module's hardware facts.

A **board base** (`catena_1sj`, `catena_5082`) defines how MCCI USES that module on Catena boards: SPI driver implementation, LED control, annunciator, vectors, EEPROM protocol, storage layout. This parallels how the existing `catena_abz` represents MCCI's common board-level usage conventions for the Murata ABZ boards. If a board doesn't follow the common conventions, a new `platform/board/xyz` collection will be needed to declare the suitable conventions; or the leaf board collection will need to call the module directly.

A **leaf board** (`catena52xx`, `catena5230`, `catena51xx`) provides the product-specific platform interface and storageInit, referencing the board base for shared functions.

## Code Reuse Strategy

Because the LED and SPI differences split cleanly across the two families:

- **52xx reuses ABZ for**: vectors, annunciator, systeminit, EEPROM, storage addresses, prepareForLaunch, delayMs, fail (all reference PB2 LED -- same pin). **New code**: SPI1 init/transfer only (in `catena_1sj`, using `module/murata-1sj` pin definitions).
- **51xx reuses ABZ for**: SPI init/transfer, EEPROM, storage addresses, prepareForLaunch, delayMs, fail (all use SPI2 PB12-15 -- same pins). **New code**: vectors, annunciator, systeminit with PB5 LED (in `catena_5082`, using `module/mcci-model5082` pin definitions).
- **5230 additionally needs**: I2C2 driver, PMIC register writes in storageInit, custom prepareForLaunch to disable LOADSW2.

The existing `flash_mx25v8035f` driver works unchanged -- it uses standard SPI NOR commands and SFDP validation, compatible with both MX25R1635F and MX25R8035F.

Storage layout: same as ABZ (fallback at 64K, update at 256K). Works for both 1MB and 2MB flash.

## New Bootloader Targets

| Target | Board(s) | Notes |
|--------|----------|-------|
| `McciBootloader_52xx` | 5210, 5220 | Simple, flash always powered |
| `McciBootloader_5230` | 5230 | PMIC-controlled flash power |
| `McciBootloader_51xx` | 5120 (and future 51xx) | Flash always powered |

---

## Implementation Phases

The phases below are ordered to get the build skeleton compiling as early as possible. Stub functions satisfy the linker first; real implementations fill in later. Each phase ends with a build checkpoint.

### Phase 1: Directory Structure

Create all directories at once. No files yet, just the tree. The structure has two levels for each new module: a `module/` directory for the hardware module definition, and a `catena_*` directory for the board-level base that wraps it (paralleling how `catena_abz` wraps the Murata ABZ module).

```
platform/board/mcci/module/
    murata-1sj/                 Murata 1SJ module hardware definition (SPI1 pins, etc.)
        i/
        mk/
        src/
    mcci-model5082/             MCCI Model 5082 module hardware definition
        i/
        mk/
        src/
platform/board/mcci/catena_1sj/ Board base for 1SJ module (calls module/murata-1sj)
    i/
    mk/
    src/
platform/board/mcci/catena52xx/ 5210/5220 leaf board
    i/
    mk/
    src/
platform/board/mcci/catena5230/ 5230 leaf board (PMIC)
    i/
    mk/
    src/
platform/board/mcci/catena_5082/ Board base for Model 5082 (calls module/mcci-model5082)
    i/
    mk/
    src/
platform/board/mcci/catena51xx/ 5120 leaf board
    i/
    mk/
    src/
```

### Phase 2: SoC Hardware Header Updates

Update `platform/soc/stm32l0/i/mcci_stm32l0xx.h` before any new headers depend on it.

#### 2.1 Fix GPIO AFR macros

Lines ~961-968: `MCCI_STM32L0_GPIO_AFRx_P(p)` and `MCCI_STM32L0_GPIO_AFSEL_P(p)` have bugs (missing `* 4` multiplier). Fix to match the STM32H7 versions. Add `MCCI_STM32L0_GPIO_AFSEL_PV(p,v)` convenience macro. Needed for I2C2 GPIO AF6 configuration on PB10/PB11.

#### 2.2 Add I2C register definitions

Add after the SPI register section (~line 1069):

**Register offsets** (Section 27.7):
- `MCCI_STM32L0_I2C_CR1` (0x00), `_CR2` (0x04), `_OAR1` (0x08), `_OAR2` (0x0C)
- `_TIMINGR` (0x10), `_TIMEOUTR` (0x14), `_ISR` (0x18), `_ICR` (0x1C)
- `_PECR` (0x20), `_RXDR` (0x24), `_TXDR` (0x28)

**Bit definitions needed** (minimum set for bootloader I2C master write):
- CR1: `PE` (bit 0)
- CR2: `SADD` (bits 0-9), `RD_WRN` (bit 10), `NBYTES` (bits 16-23), `START` (bit 13), `STOP` (bit 14), `AUTOEND` (bit 25)
- ISR: `TXE` (bit 0), `TXIS` (bit 1), `NACKF` (bit 4), `STOPF` (bit 5), `TC` (bit 6), `BUSY` (bit 15)
- ICR: `NACKCF` (bit 4), `STOPCF` (bit 5)
- TIMINGR: `PRESC` (bits 28-31), `SCLDEL` (bits 20-23), `SDADEL` (bits 16-19), `SCLH` (bits 8-15), `SCLL` (bits 0-7)

Follow existing naming pattern: `MCCI_STM32L0_I2C_CR1_PE`, `MCCI_STM32L0_I2C_CR2_SADD`, etc.

I2C base addresses already defined: `MCCI_STM32L0_REG_I2C1` (0x40005400), `MCCI_STM32L0_REG_I2C2` (0x40005800). RCC enable/reset bits already defined: `MCCI_STM32L0_REG_RCC_APB1ENR_I2C2EN`, `MCCI_STM32L0_REG_RCC_APB1RSTR_I2C2RST`. SPI1 clock definitions already exist: `MCCI_STM32L0_REG_RCC_APB2ENR_SPI1EN` (line 657), `MCCI_STM32L0_REG_RCC_APB2RSTR_SPI1RST` (line 584).

**Checkpoint**: Existing targets still build cleanly.

### Phase 3: Header Files

Create all new header files, module headers first (since board base headers depend on them), then board base headers, then leaf board headers.

#### 3a: Module hardware definition headers

These are header-only, defining the module's hardware facts as macros.

#### 3a.1 `module/murata-1sj/i/mcci_bootloader_module_murata_1sj.h`
- Include guard, include `mcci_stm32l0xx.h`
- SPI: `SPI1` base, GPIOA, pins 4/5/6/7, AF0, APB2 clock enable/reset bits
- LED: GPIOB, pin 2, IOPBEN clock bit
- I2C2: base, GPIOB, pins 10/11, AF6, APB1 clock enable/reset bits (available for boards that need it)

#### 3a.2 `module/mcci-model5082/i/mcci_bootloader_module_model5082.h`
- Include guard, include `mcci_stm32l0xx.h`
- SPI: `SPI2` base, GPIOB, pins 12/13/14/15, AF0, APB1 clock enable/reset bits
- LED: GPIOB, pin 5, IOPBEN clock bit
- Note: PB2 = RF_RESET on this module (document as "do not use for LED")

#### 3b: Board base headers

#### 3b.1 `catena_1sj/i/mcci_bootloader_board_catena_1sj.h`
- Include guard, include `mcci_bootloader_platform.h` and `mcci_bootloader_module_murata_1sj.h`
- Declare `McciBootloaderBoard_Catena1sj_spiInit` (SpiInitFn_t)
- Declare `McciBootloaderBoard_Catena1sj_spiTransfer` (SpiTransferFn_t)

#### 3b.2 `catena_5082/i/mcci_bootloader_board_catena_5082.h`
- Model on `mcci_bootloader_board_catena_abz.h`
- Include `mcci_bootloader_module_model5082.h`
- All function declarations use `McciBootloaderBoard_Catena5082_` prefix:
  - systemInit, prepareForLaunch, fail, delayMs, setLed, clearLed
  - getUpdate, setUpdate (EEPROM)
  - getPrimaryStorageAddress, getFallbackStorageAddress
  - annunciatorInit, annunciatorIndicateState, handleSysTick
- Storage layout constants with `_5082_` prefix (same values as ABZ: 168K image, 64K fallback, 256K update)

#### 3b.3 `catena_5082/i/mcci_bootloader_board_catena_5082_eeprom.h`
- Copy from `mcci_bootloader_board_catena_abz_eeprom.h` with name changes (`CatenaAbz` -> `Catena5082`)

#### 3c: Leaf board headers

#### 3c.1 `catena52xx/i/mcci_bootloader_board_catena52xx.h`
- Include `mcci_bootloader_board_catena_abz.h` and `mcci_bootloader_board_catena_1sj.h`
- Declare `McciBootloaderBoard_Catena52xx_storageInit` (StorageInitFn_t)

#### 3c.2 `catena5230/i/mcci_bootloader_board_catena5230.h`
- Include `mcci_bootloader_board_catena_abz.h` and `mcci_bootloader_board_catena_1sj.h`
- Declare `McciBootloaderBoard_Catena5230_storageInit` (StorageInitFn_t)
- Declare `McciBootloaderBoard_Catena5230_prepareForLaunch` (PrepareForLaunchFn_t)

#### 3c.3 `catena51xx/i/mcci_bootloader_board_catena51xx.h`
- Include `mcci_bootloader_board_catena_5082.h`
- Declare `McciBootloaderBoard_Catena51xx_storageInit` (StorageInitFn_t)

**Checkpoint**: Each header compiles standalone (see Phase 4).

### Phase 4: Header Compile Tests

Create a test that compiles each new header file standalone to verify it is self-contained and standards-compliant. One `.c` file per header:

```c
/* test compile for mcci_bootloader_board_catena_1sj.h */
#include "mcci_bootloader_board_catena_1sj.h"
```

Compile with `-fsyntax-only -Wall -Werror -std=gnu11` and the appropriate include paths. This can be a small makefile target or a shell loop. The goal is to confirm every header includes its own dependencies and has no syntax errors.

**Checkpoint**: All header compile tests pass.

### Phase 5: Makefile Hierarchy

Create all makefiles for all boards. These reference source files that will be stubs initially.

#### 5.1 `catena_1sj/mk/libmcci_bootloader_catena_1sj.mk`
- Include guard
- Include `libmcci_bootloader_catena_abz.mk` (for INCLUDES)
- Library: `libmcci_bootloader_catena_1sj`
- Sources: `mccibootloaderboard_catena1sj_spi.c`
- Includes: catena_abz includes + `$_/i`

#### 5.2 `catena52xx/mk/libmcci_bootloader_catena52xx.mk`
- Prerequisites: `libmcci_bootloader_catena_abz.mk`, `libmcci_bootloader_catena_1sj.mk`, `libmcci_bootloader_flash_mx25v8035f.mk`
- Sources: platforminterface.c, storageinit.c
- Includes: catena_abz includes + catena_1sj includes + flash driver includes + `$_/i`

#### 5.3 `catena52xx/mk/mcci_bootloader_52xx.mk`
- `include platform/board/mcci/catena_abz/mk/mcci_bootloader_catena_abz.mk`
- `BOOTLOADERS += McciBootloader_52xx`
- LIBS: `${BOOTLOADER_LIBS_ABZ}` + `libmcci_bootloader_catena_1sj.a` + `libmcci_bootloader_catena52xx.a`
- LDSCRIPT: `${BOOTLOADER_LDSCRIPT_ABZ}`

#### 5.4 `catena5230/mk/libmcci_bootloader_catena5230.mk`
- Same prerequisites as catena52xx
- Sources: platforminterface.c, storageinit.c, prepareforlaunch.c

#### 5.5 `catena5230/mk/mcci_bootloader_5230.mk`
- Same as 52xx pattern but `BOOTLOADERS += McciBootloader_5230` and uses catena5230 library

#### 5.6 `catena_5082/mk/libmcci_bootloader_catena_5082.mk`
- Include `libmcci_bootloader_stm32l0.mk`
- Sources: annunciator.c, eeprom.c, prepareforlaunch.c, storage.c, systeminit.c, vectors.c
- Includes: stm32l0 includes + `$_/i`

#### 5.7 `catena_5082/mk/mcci_bootloader_catena_5082.mk`
- Defines `BOOTLOADER_LIBS_5082` (cm0plus + stm32l0 + catena_5082 + flash_mx25v8035f)
- Defines `BOOTLOADER_LDSCRIPT_5082`

#### 5.8 `catena_5082/mk/mccibootloader.ld`
- Copy from ABZ `mccibootloader.ld`
- Change EEPROM symbol names to `Catena5082`
- Same memory sizes (192K flash, 20K RAM, 6K EEPROM for STM32L082)

#### 5.9 `catena51xx/mk/libmcci_bootloader_catena51xx.mk`
- Prerequisites: `libmcci_bootloader_catena_5082.mk`, `libmcci_bootloader_catena_abz.mk`, `libmcci_bootloader_flash_mx25v8035f.mk`
- Sources: platforminterface.c, storageinit.c

#### 5.10 `catena51xx/mk/mcci_bootloader_51xx.mk`
- `BOOTLOADERS += McciBootloader_51xx`
- LIBS: `${BOOTLOADER_LIBS_5082}` + `libmcci_bootloader_catena_abz.a` + `libmcci_bootloader_catena51xx.a`
- LDSCRIPT: `${BOOTLOADER_LDSCRIPT_5082}`

#### 5.11 Update `Makefile-stm32l0.mk`

After the existing includes for catena4801 and catena46xx, add:
```makefile
include platform/board/mcci/catena52xx/mk/mcci_bootloader_52xx.mk
include platform/board/mcci/catena5230/mk/mcci_bootloader_5230.mk
include platform/board/mcci/catena51xx/mk/mcci_bootloader_51xx.mk
```

**Checkpoint**: `make -f Makefile-stm32l0.mk` discovers all targets (may fail on missing sources -- that's expected, confirms makefile wiring).

### Phase 6: Stub C Implementations

Create all `.c` source files with correct headers, includes, and function signatures, but with empty/minimal bodies. Each file should compile. Functions that must return a value return 0 or a safe default. The goal is a linking build.

#### 6.1 catena_1sj stubs
- `mccibootloaderboard_catena1sj_spi.c`: empty `spiInit()`, empty-loop `spiTransfer()`

#### 6.2 catena52xx stubs
- `mccibootloaderboard_catena52xx_platforminterface.c`: full `gk_McciBootloaderPlatformInterface` struct wired to ABZ functions (systemInit, prepareForLaunch, fail, delayMs, getUpdate, setUpdate, annunciator, storage addresses) + Catena1sj SPI + board-specific storageInit. This file is complete, not a stub.
- `mccibootloaderboard_catena52xx_storageinit.c`: empty `storageInit()`

#### 6.3 catena5230 stubs
- `mccibootloaderboard_catena5230_platforminterface.c`: same as 52xx but we needto override `.pSystemInit` = `Catena5230_systemInit`, `.Storage.pInit` = `Catena5230_storageInit`, `.pPrepareForLaunch` = `Catena5230_prepareForLaunch`. This file is complete, not a stub.
- `mccibootloaderboard_catena5230_storageinit.c`: empty `storageInit()`
- `mccibootloaderboard_catena5230_prepareforlaunch.c`: stub that just calls `McciBootloader_Stm32L0_prepareForLaunch()`

#### 6.4 catena_5082 stubs
- `mccibootloaderboard_catena5082_systeminit.c`: stub systemInit (calls `McciBootloader_Stm32L0_systemInit()` only), empty setLed/clearLed/delayMs/fail/fastBlinkForever
- `mccibootloaderboard_catena5082_annunciator.c`: empty annunciatorInit/annunciatorIndicateState/handleSysTick
- `mccibootloaderboard_catena5082_vectors.c`: copy from ABZ vectors with name changes to `Catena5082_` prefix. This file is structurally complete (vector table must be correct for linking).
- `mccibootloaderboard_catena5082_eeprom.c`: copy from ABZ with name changes. Structurally complete (simple EEPROM access).
- `mccibootloaderboard_catena5082_storage.c`: copy from ABZ with name changes and `_5082_` constants. Structurally complete.
- `mccibootloaderboard_catena5082_prepareforlaunch.c`: calls `McciBootloader_Stm32L0_prepareForLaunch()`. Structurally complete.

#### 6.5 catena51xx stubs
- `mccibootloaderboard_catena51xx_platforminterface.c`: full struct wired to Catena5082 functions (systemInit, prepareForLaunch, fail, delayMs, getUpdate, setUpdate, annunciator, storage addresses) + ABZ SPI + board-specific storageInit. Complete, not a stub.
- `mccibootloaderboard_catena51xx_storageinit.c`: empty `storageInit()`

**Checkpoint**: `CROSS_COMPILE=... make -f Makefile-stm32l0.mk` compiles and links all five bootloaders (existing two + three new). New bootloaders are non-functional but structurally valid.

### Phase 7: Fill In Real Implementations

With the skeleton building, fill in real function bodies. Each step is independently testable.

#### 7.1 catena_1sj SPI1 driver
- Model on `catena_abz/src/mccibootloaderboard_catenaabz_spi.c`
- **spiInit**: Enable GPIOA clock (`IOPAEN`), configure PA4/PA5/PA6/PA7 as AF mode, high speed, PA5 pulldown. Enable SPI1 via `RCC_APB2ENR_SPI1EN`. Reset via `RCC_APB2RSTR_SPI1RST`. Configure SPI1 CR1 (`BR_2 | MSTR`) and CR2 (`SSOE`). All AF0, no AFR writes needed.
- **spiTransfer**: Same logic as ABZ but use `MCCI_STM32L0_REG_SPI1` instead of `MCCI_STM32L0_REG_SPI2`.

#### 7.2 catena52xx storageInit
- Simple: `McciBootloaderPlatform_spiInit()` + `McciBootloaderFlash_Mx25v8035f_storageInit()` (same pattern as catena46xx)

#### 7.3 catena_5082 systeminit and LED
- Model on ABZ systeminit
- Enable GPIOB clock (same port as ABZ)
- Configure **PB5** as output (instead of PB2)
- `setLed`/`clearLed`/`delayMs`/`fail`/`fastBlinkForever` use PB5 bit masks
- Note: PB2 on the 5082/5120 is RF_RESET -- must NOT be driven by the bootloader

#### 7.4 catena_5082 annunciator
- Copy logic from ABZ annunciator, already has correct `Catena5082_` names from stub phase
- Fill in real state machine referencing `McciBootloaderBoard_Catena5082_setLed/clearLed`

#### 7.5 catena51xx storageInit
- Simple: `McciBootloaderPlatform_spiInit()` + `McciBootloaderFlash_Mx25v8035f_storageInit()` (no power control needed, flash on +VDD)

#### 7.6 catena5230 storageInit (most complex new code)

Sequence:
1. Enable GPIOB clock (for I2C2 pins PB10/PB11)
2. Configure PB10 (SCL) as AF open-drain with pull-up, AF6 (I2C2_SCL)
3. Configure PB11 (SDA) as AF open-drain with pull-up, AF6 (I2C2_SDA)
4. Enable I2C2 clock (`RCC_APB1ENR_I2C2EN`)
5. Reset I2C2 (`RCC_APB1RSTR_I2C2RST`)
6. Set I2C2 TIMINGR for 100 kHz from 32 MHz PCLK1 (value ~`0x10805E89`, verify from RM)
7. Enable I2C2 (set PE in CR1)
8. I2C write to 0x6B: `[0x08, 0x09, 0x00]` -- select LOADSW2 as load switch
9. I2C write to 0x6B: `[0x08, 0x02, 0x01]` -- enable LOADSW2 (task trigger)
10. Delay 50ms for power stabilization
11. `McciBootloaderPlatform_spiInit()` -- init SPI1
12. `McciBootloaderFlash_Mx25v8035f_storageInit()` -- init flash

I2C write transaction (each 3-byte write):
- Set CR2: slave addr `(0x6B << 1)`, NBYTES=3, write, START, AUTOEND
- Poll ISR.TXIS, write byte to TXDR (repeat x3)
- Poll ISR.STOPF, clear via ICR.STOPCF

**Driver layering note**: The I2C and PMIC operations could be structured as separate drivers (PMIC over I2C) or kept inline in storageinit. This architectural decision is left to the implementer.

#### 7.7 catena5230 prepareForLaunch (custom)

The PMIC's LOADSW2 setting is latched in the NPM1300's internal registers and survives MCU peripheral reset. To achieve micropower state before app launch:

1. I2C write to 0x6B: `[0x08, 0x03, 0x01]` -- disable LOADSW2 (task trigger on LDSW2 disable register 0x0803)
2. Poll ISR.STOPF, clear
3. Call `McciBootloader_Stm32L0_prepareForLaunch()` -- resets all MCU peripherals including I2C2, switches to MSI

I2C2 is still configured from storageInit, so the disable command can be sent directly.

### Phase 8: Hardware Verification

1. **Size check**: Each bootloader must fit in 20K (0x5000). The 5230 with I2C code is the largest -- estimate ~1-2K additional over the base ~14K
2. **Binary inspection**: Verify vector table at 0x08000000, AppInfo offset at 0xC0
3. **Hardware test** (per board):
   - Flash bootloader at 0x08000000 via st-flash
   - Observe LED blink pattern (failure expected, no app)
   - Sign test app with `mccibootloader_image`, place in SPI flash update region
   - Set EEPROM update request flag
   - Power cycle -- verify bootloader programs app from SPI flash
   - Verify app launches successfully
4. **5230-specific**: Verify LOADSW2 enables (flash powers up), bootloader works, and LOADSW2 disables in prepareForLaunch (measure current)

---

## Dependency Graph

```
Phase 1 (directories)
  |
Phase 2 (SoC header: I2C regs, AFR fix)
  |
Phase 3 (all interface headers)
  |
Phase 4 (header compile tests)
  |
Phase 5 (all makefiles + Makefile-stm32l0.mk)
  |
Phase 6 (stub .c files -- all targets compile and link)
  |
Phase 7 (real implementations, independently)
  +---> 7.1 1SJ SPI1 driver
  +---> 7.2 52xx storageInit
  +---> 7.3 5082 systeminit/LED
  +---> 7.4 5082 annunciator
  +---> 7.5 51xx storageInit
  +---> 7.6 5230 storageInit (I2C + PMIC)
  +---> 7.7 5230 prepareForLaunch
  |
Phase 8 (hardware verification)
```

Within Phase 7, steps 7.1-7.2 (52xx) and 7.3-7.5 (51xx) are independent. Steps 7.6-7.7 depend on 7.1 (SPI1 must work before 5230 can be tested end-to-end).

## Open Items for Implementer

1. **I2C TIMINGR value**: Must be calculated or verified for 100 kHz from 32 MHz PCLK1. Candidate: `0x10805E89`. Consult STM32L0 RM Section 27.4.9 or use STM32CubeMX.
2. **I2C/PMIC driver layering**: The plan describes register-level operations inline in storageinit. The implementer may choose to factor I2C into a separate driver module and/or create a PMIC abstraction. The need for this is identified; the architecture is left to the implementer.
3. **AF6 for I2C2**: PB10=I2C2_SCL(AF6), PB11=I2C2_SDA(AF6) per STM32L072 datasheet Table 17. Requires AFR register writes (the fixed macros from Phase 2.1).
4. **NPM1300 LOADSW2 disable register**: Verify 0x0803 is the correct task-disable register for LDSW2. The enable task register is 0x0802 (confirmed from cNPM1300 library).

## Key Source Files to Reference

| Template | Use for | Path |
|----------|---------|------|
| ABZ SPI | 1SJ SPI1 | `platform/board/mcci/catena_abz/src/mccibootloaderboard_catenaabz_spi.c` |
| 4801 storageInit | 5230 storageInit | `platform/board/mcci/catena4801/src/mccibootloaderboard_catena4801_storageinit.c` |
| 46xx platforminterface | 52xx/51xx platforminterface | `platform/board/mcci/catena46xx/src/mccibootloaderboard_catena46xx_platforminterface.c` |
| ABZ annunciator | 5082 annunciator | `platform/board/mcci/catena_abz/src/mccibootloaderboard_catenaabz_annunciator.c` |
| ABZ systeminit | 5082 systeminit | `platform/board/mcci/catena_abz/src/mccibootloaderboard_catenaabz_systeminit.c` |
| ABZ vectors | 5082 vectors | `platform/board/mcci/catena_abz/src/mccibootloaderboard_catenaabz_vectors.c` |
| ABZ base makefile | 5082 base makefile | `platform/board/mcci/catena_abz/mk/mcci_bootloader_catena_abz.mk` |
| ABZ linker script | 5082 linker script | `platform/board/mcci/catena_abz/mk/mccibootloader.ld` |
| 46xx bootloader mk | 52xx/51xx bootloader mk | `platform/board/mcci/catena46xx/mk/mcci_bootloader_46xx.mk` |
| STM32L0 registers | I2C register additions | `platform/soc/stm32l0/i/mcci_stm32l0xx.h` |
| NPM1300 library | PMIC register reference | (external: `COLLECTION-Catena5230/libraries/MCCI-Catena-nPM1300/src/MCCI_Catena_nPM1300.h`) |
