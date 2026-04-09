# Plan: Add Catena 51xx and 52xx Bootloader Support

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

## Code Reuse Strategy

Because the LED and SPI differences split cleanly across the two families:

- **52xx reuses ABZ for**: vectors, annunciator, systeminit, EEPROM, storage addresses, prepareForLaunch, delayMs, fail (all reference PB2 LED -- same pin). **New code**: SPI1 init/transfer only.
- **51xx reuses ABZ for**: SPI init/transfer, EEPROM, storage addresses, prepareForLaunch, delayMs, fail (all use SPI2 PB12-15 -- same pins). **New code**: vectors, annunciator, systeminit with PB5 LED.
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

## Phase 0: SoC Header Updates

### 0.1 Add I2C register definitions to `platform/soc/stm32l0/i/mcci_stm32l0xx.h`

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

I2C base addresses already defined: `MCCI_STM32L0_REG_I2C1` (0x40005400), `MCCI_STM32L0_REG_I2C2` (0x40005800). RCC enable/reset bits already defined: `MCCI_STM32L0_REG_RCC_APB1ENR_I2C2EN`, `MCCI_STM32L0_REG_RCC_APB1RSTR_I2C2RST`.

### 0.2 Fix GPIO AFR macros in same file

Lines ~961-968: `MCCI_STM32L0_GPIO_AFRx_P(p)` and `MCCI_STM32L0_GPIO_AFSEL_P(p)` have bugs (missing `* 4` multiplier). Fix to match the STM32H7 versions. Add `MCCI_STM32L0_GPIO_AFSEL_PV(p,v)` convenience macro.

These are needed for I2C2 GPIO alternate function configuration (AF6 for PB10/PB11).

### 0.3 Add SPI1 clock definitions if missing

Verify `MCCI_STM32L0_REG_RCC_APB2ENR_SPI1EN` and `MCCI_STM32L0_REG_RCC_APB2RSTR_SPI1RST` exist (they do, confirmed at lines 584/657).

---

## Phase 1: SPI1 Shared Code for 52xx (catena_1sj)

Create a minimal shared library containing only the SPI1 driver, shared by both catena52xx and catena5230.

### Directory structure
```
platform/board/mcci/catena_1sj/
    i/mcci_bootloader_board_catena_1sj.h
    mk/libmcci_bootloader_catena_1sj.mk
    src/mccibootloaderboard_catena1sj_spi.c
```

### 1.1 Header: `mcci_bootloader_board_catena_1sj.h`
- Include guard, include `mcci_bootloader_platform.h`
- Declare `McciBootloaderBoard_Catena1sj_spiInit` (SpiInitFn_t)
- Declare `McciBootloaderBoard_Catena1sj_spiTransfer` (SpiTransferFn_t)

### 1.2 SPI driver: `mccibootloaderboard_catena1sj_spi.c`
- Model on `catena_abz/src/mccibootloaderboard_catenaabz_spi.c`
- **spiInit**: Enable GPIOA clock (`IOPAEN`), configure PA4/PA5/PA6/PA7 as AF mode (MODER), high speed (OSPEEDR), PA5 pulldown (PUPDR). Enable SPI1 via `RCC_APB2ENR_SPI1EN`. Reset via `RCC_APB2RSTR_SPI1RST`. Configure SPI1 CR1 (`BR_2 | MSTR`) and CR2 (`SSOE`). All AF0, no AFR writes needed.
- **spiTransfer**: Same logic as ABZ but use `MCCI_STM32L0_REG_SPI1` instead of `MCCI_STM32L0_REG_SPI2`.

### 1.3 Library makefile: `libmcci_bootloader_catena_1sj.mk`
- Include guard
- Include `libmcci_bootloader_catena_abz.mk` (for INCLUDES, which pull in stm32l0 headers)
- Library: `libmcci_bootloader_catena_1sj`
- Sources: `mccibootloaderboard_catena1sj_spi.c`
- Includes: catena_abz includes + `$_/i`

---

## Phase 2: Catena 52xx Leaf Board (5210/5220)

### Directory structure
```
platform/board/mcci/catena52xx/
    i/mcci_bootloader_board_catena52xx.h
    mk/mcci_bootloader_52xx.mk
    mk/libmcci_bootloader_catena52xx.mk
    src/mccibootloaderboard_catena52xx_platforminterface.c
    src/mccibootloaderboard_catena52xx_storageinit.c
```

### 2.1 Header
- Include `mcci_bootloader_board_catena_abz.h` and `mcci_bootloader_board_catena_1sj.h`
- Declare `McciBootloaderBoard_Catena52xx_storageInit`

### 2.2 Platform interface
- Model on `catena46xx/src/mccibootloaderboard_catena46xx_platforminterface.c`
- `gk_McciBootloaderPlatformInterface` references:
  - All ABZ functions for: systemInit, prepareForLaunch, fail, delayMs, getUpdate, setUpdate, annunciator, storage addresses
  - STM32L0 functions for: flashErase, flashWrite
  - **Catena1sj** functions for: spiInit, spiTransfer (the SPI1 code)
  - Flash driver for: storageRead
  - Board-specific: storageInit

### 2.3 Storage init
- Simple: `McciBootloaderPlatform_spiInit()` + `McciBootloaderFlash_Mx25v8035f_storageInit()` (same as catena46xx)

### 2.4 Bootloader makefile (`mcci_bootloader_52xx.mk`)
- `include platform/board/mcci/catena_abz/mk/mcci_bootloader_catena_abz.mk`
- `BOOTLOADERS += McciBootloader_52xx`
- LIBS: `${BOOTLOADER_LIBS_ABZ}` + `libmcci_bootloader_catena_1sj.a` + `libmcci_bootloader_catena52xx.a`
- LDSCRIPT: `${BOOTLOADER_LDSCRIPT_ABZ}`

### 2.5 Library makefile (`libmcci_bootloader_catena52xx.mk`)
- Prerequisites: `libmcci_bootloader_catena_abz.mk`, `libmcci_bootloader_catena_1sj.mk`, `libmcci_bootloader_flash_mx25v8035f.mk`
- Sources: platforminterface.c, storageinit.c
- Includes: catena_abz includes + catena_1sj includes + flash driver includes + `$_/i`

---

## Phase 3: Catena 5230 Leaf Board (PMIC)

### Directory structure
```
platform/board/mcci/catena5230/
    i/mcci_bootloader_board_catena5230.h
    mk/mcci_bootloader_5230.mk
    mk/libmcci_bootloader_catena5230.mk
    src/mccibootloaderboard_catena5230_platforminterface.c
    src/mccibootloaderboard_catena5230_storageinit.c
    src/mccibootloaderboard_catena5230_prepareforlaunch.c
```

### 3.1 Header
- Include `mcci_bootloader_board_catena_abz.h` and `mcci_bootloader_board_catena_1sj.h`
- Declare `McciBootloaderBoard_Catena5230_storageInit`
- Declare `McciBootloaderBoard_Catena5230_prepareForLaunch`

### 3.2 Platform interface
- Same as catena52xx EXCEPT:
  - `.Storage.pInit` = `McciBootloaderBoard_Catena5230_storageInit`
  - `.pPrepareForLaunch` = `McciBootloaderBoard_Catena5230_prepareForLaunch` (custom, not ABZ)

### 3.3 Storage init (most complex new file)

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

**Driver layering note**: The I2C and PMIC operations could be structured as separate drivers (PMIC over I2C) or kept inline in storageinit. This architectural decision is left to the implementer. The minimum requirement is the register-level operations described above.

### 3.4 Prepare for launch (custom)

The PMIC's LOADSW2 setting is latched in the NPM1300's internal registers and survives MCU peripheral reset. To achieve micropower state before app launch:

1. I2C write to 0x6B: `[0x08, 0x03, 0x01]` -- disable LOADSW2 (task trigger on LDSW2 disable register 0x0803)
2. Poll ISR.STOPF, clear
3. Call `McciBootloader_Stm32L0_prepareForLaunch()` -- resets all MCU peripherals including I2C2, switches to MSI

I2C2 is still configured from storageInit, so the disable command can be sent directly.

### 3.5 Build files
- Same structure as Phase 2 but include prepareforlaunch.c in sources

---

## Phase 4: Model 5082 Shared Base for 51xx (catena_5082)

The 5082 uses the same SPI2 as ABZ but different LED pin (PB5 vs PB2). The LED-coupled code (systeminit, annunciator, vectors) must be reimplemented. SPI, EEPROM, storage, and prepareForLaunch from ABZ can be reused directly via the platform interface.

### Directory structure
```
platform/board/mcci/catena_5082/
    i/mcci_bootloader_board_catena_5082.h
    i/mcci_bootloader_board_catena_5082_eeprom.h
    mk/libmcci_bootloader_catena_5082.mk
    mk/mcci_bootloader_catena_5082.mk
    mk/mccibootloader.ld
    src/mccibootloaderboard_catena5082_annunciator.c
    src/mccibootloaderboard_catena5082_eeprom.c
    src/mccibootloaderboard_catena5082_prepareforlaunch.c
    src/mccibootloaderboard_catena5082_storage.c
    src/mccibootloaderboard_catena5082_systeminit.c
    src/mccibootloaderboard_catena5082_vectors.c
```

### 4.1 Header (`mcci_bootloader_board_catena_5082.h`)
- Model on `mcci_bootloader_board_catena_abz.h`
- All function declarations use `McciBootloaderBoard_Catena5082_` prefix
- Same storage layout constants (168K image, 64K fallback, 256K update) but with `_5082_` prefix

### 4.2 systeminit
- Model on ABZ systeminit
- Enable GPIOB clock (same port as ABZ)
- Configure **PB5** as output (instead of PB2)
- `setLed`/`clearLed`/`delayMs`/`fail`/`fastBlinkForever` use PB5 bit masks
- Note: PB2 on the 5082/5120 is RF_RESET -- must NOT be driven by the bootloader

### 4.3 annunciator
- Copy from ABZ annunciator, change all names to `Catena5082_` prefix
- References `McciBootloaderBoard_Catena5082_setLed/clearLed`

### 4.4 vectors
- Copy from ABZ vectors, change all names to `Catena5082_` prefix
- SysTick handler calls `McciBootloaderBoard_Catena5082_handleSysTick`

### 4.5 EEPROM, storage, prepareForLaunch
- Copy from ABZ with name changes (`CatenaAbz_` -> `Catena5082_`)
- Same logic (STM32L0 data EEPROM at 0x08080000, same storage addresses)
- prepareForLaunch: calls `McciBootloader_Stm32L0_prepareForLaunch()` (same as ABZ)

### 4.6 Linker script
- Copy from ABZ `mccibootloader.ld`
- Change EEPROM symbol names to `Catena5082`
- Same memory sizes (192K flash, 20K RAM, 6K EEPROM for STM32L082)

### 4.7 Library makefile (`libmcci_bootloader_catena_5082.mk`)
- Include `libmcci_bootloader_stm32l0.mk`
- Sources: all 6 `.c` files
- Includes: stm32l0 includes + `$_/i`

### 4.8 Base makefile (`mcci_bootloader_catena_5082.mk`)
- Defines `BOOTLOADER_LIBS_5082` (cm0plus + stm32l0 + catena_5082 + flash_mx25v8035f)
- Defines `BOOTLOADER_LDSCRIPT_5082`

---

## Phase 5: Catena 51xx Leaf Board

### Directory structure
```
platform/board/mcci/catena51xx/
    i/mcci_bootloader_board_catena51xx.h
    mk/mcci_bootloader_51xx.mk
    mk/libmcci_bootloader_catena51xx.mk
    src/mccibootloaderboard_catena51xx_platforminterface.c
    src/mccibootloaderboard_catena51xx_storageinit.c
```

### 5.1 Header
- Include `mcci_bootloader_board_catena_5082.h`
- Declare `McciBootloaderBoard_Catena51xx_storageInit`

### 5.2 Platform interface
- `gk_McciBootloaderPlatformInterface` references:
  - **Catena5082** functions for: systemInit, prepareForLaunch, fail, delayMs, getUpdate, setUpdate, annunciator, storage addresses (all use PB5 LED)
  - STM32L0 functions for: flashErase, flashWrite
  - **ABZ** functions for: spiInit, spiTransfer (SPI2 on PB12-15 -- same as ABZ!)
  - Flash driver for: storageRead
  - Board-specific: storageInit

### 5.3 Storage init
- Simple: `McciBootloaderPlatform_spiInit()` + `McciBootloaderFlash_Mx25v8035f_storageInit()` (no power control needed, flash on +VDD)

### 5.4 Build files
- `BOOTLOADERS += McciBootloader_51xx`
- LIBS: `${BOOTLOADER_LIBS_5082}` + ABZ SPI library + `libmcci_bootloader_catena51xx.a`

Note: The 51xx platform interface references ABZ SPI functions. The ABZ library object containing SPI code will be pulled by the linker from `libmcci_bootloader_catena_abz.a`. Include `libmcci_bootloader_catena_abz.mk` in the 51xx library makefile to get the ABZ SPI header paths, and add `libmcci_bootloader_catena_abz.a` to the LIBS list.

---

## Phase 6: Build System Integration

### Update `Makefile-stm32l0.mk`

After the existing includes for catena4801 and catena46xx, add:
```makefile
include platform/board/mcci/catena52xx/mk/mcci_bootloader_52xx.mk
include platform/board/mcci/catena5230/mk/mcci_bootloader_5230.mk
include platform/board/mcci/catena51xx/mk/mcci_bootloader_51xx.mk
```

This produces three new ELF/BIN/HEX files in the build output directory.

---

## Phase 7: Verification

1. **Build all targets**: `CROSS_COMPILE=... make -f Makefile-stm32l0.mk` -- verify no errors
2. **Size check**: Each bootloader must fit in 20K (0x5000). The 5230 with I2C code is the largest -- estimate ~1-2K additional over the base ~14K
3. **Binary inspection**: Verify vector table at 0x08000000, AppInfo offset at 0xC0
4. **Hardware test** (per board):
   - Flash bootloader at 0x08000000 via st-flash
   - Observe LED blink pattern (failure expected, no app)
   - Sign test app, load to SPI flash update region
   - Set EEPROM update flag, power cycle
   - Verify app programs and launches
5. **5230-specific**: Verify LOADSW2 enables (flash powers up), bootloader works, and LOADSW2 disables in prepareForLaunch (measure current)

---

## Dependency Graph

```
Phase 0 (mcci_stm32l0xx.h: I2C regs, AFR fix)
  |
  +---> Phase 1 (catena_1sj SPI1 code)
  |       |
  |       +---> Phase 2 (catena52xx leaf) ----+
  |       |                                    |
  |       +---> Phase 3 (catena5230 leaf) ----+---> Phase 6 (Makefile)
  |                                            |         |
  +---> Phase 4 (catena_5082 base)            |    Phase 7 (test)
          |                                    |
          +---> Phase 5 (catena51xx leaf) -----+
```

Phases 1-3 and Phases 4-5 are independent of each other.

## Open Items for Implementer

1. **I2C TIMINGR value**: Must be calculated or verified for 100 kHz from 32 MHz PCLK1. Candidate: `0x10805E89`. Consult STM32L0 RM Section 27.4.9 or use STM32CubeMX.
2. **I2C/PMIC driver layering**: The plan describes register-level operations inline in storageinit. The implementer may choose to factor I2C into a separate driver module and/or create a PMIC abstraction. The need for this is identified; the architecture is left to the implementer.
3. **AF6 for I2C2**: PB10=I2C2_SCL(AF6), PB11=I2C2_SDA(AF6) per STM32L072 datasheet Table 17. Requires AFR register writes (the fixed macros from Phase 0.2).
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
| 46xx bootloader mk | 52xx/51xx bootloader mk | `platform/board/mcci/catena46xx/mk/mcci_bootloader_46xx.mk` |
| STM32L0 registers | I2C register additions | `platform/soc/stm32l0/i/mcci_stm32l0xx.h` |
| NPM1300 library | PMIC register reference | (external: `COLLECTION-Catena5230/libraries/MCCI-Catena-nPM1300/src/MCCI_Catena_nPM1300.h`) |
