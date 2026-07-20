# Punch list: I2C bus driver and portable-API follow-ups

Temporary file; delete when done.

## Portable I2C API

- [x] Add an error/status return to the portable I2C read/write API
      (`McciBootloaderDeviceI2cBus_ReadFn_t` / `WriteFn_t` and the device-layer
      equivalents in `driver/i2c/i/`). Today they return bytes transferred
      (`nBuffer_orig - nBuffer`). A zero-length probe returns 0 whether the device
      ACKed or NACKed, so presence can't be reported, and callers can't tell
      timeout / arb-loss / NACK / bus-error apart. The STM32L0 driver already
      tracks all of these in its `..._Status_t` enum -- surface it. Cheap to add
      now, annoying to thread through later.

### Detailed plan for the error return

Decisions to settle first:

- [x] **Return convention.** Recommend: return the result code, and add a nullable
      `size_t *pnActual` out-param for bytes transferred. Callers that only care
      about success ignore it; a probe passes NULL. (Alternative: keep the byte
      count as the return and add a status out-param -- rejected, keeps the
      "0 is ambiguous" problem.) See implementation.
- [x] **Result type.** Mirror the `McciBootloaderError_t` pattern exactly: a
      fixed-width `typedef uint32_t McciBootloaderDeviceI2cResult_t;` (the actual
      return type -- portable width) plus a separate `enum
      McciBootloaderDeviceI2cResult_e { ... }` for the named values. Model:
      `i/mcci_bootloader_types.h:81` (the `_t`) and `i/mcci_bootloader.h:53` (the
      `enum _e`); copy the width caveat comment from
      `i/mcci_bootloader_types.h:91-98` (State_t).
      Values to define: `_OK`=0, `_Timeout`, `_ArbitrationLost`, `_Nack`,
      `_BusError` (map from the SoC enum below).
      See implementation.
- [x] **New type vs. reuse.** Alternative to a new type: add `_I2cNack`,
      `_I2cTimeout`, `_I2cArbLost`, `_I2cBusError` to the existing
      `McciBootloaderError_e` (which already has `_I2cBegin`) and return
      `McciBootloaderError_t`. The i2c driver already depends on that enum
      (`McciBootloaderPlatform_fail` calls), so this avoids a parallel type and a
      mapping step. Pick one; the touch list below assumes the new i2c-specific
      type. See implementation.

Abstract i2c layer (`driver/i2c/i/`):

- [x] `mcci_bootloader_device_i2c_common_types.h` -- add `McciBootloaderDeviceI2cResult_t`
      (next to `McciBootloaderDeviceI2cAddress_t`, line 37). Put the `enum
      ..._Result_e` here too, or in a new `mcci_bootloader_device_i2c_common.h` if you
      want strict types.h/enum split parity with the State pattern.
- [x] `mcci_bootloader_device_i2c_bus_types.h` -- `McciBootloaderDeviceI2cBus_ReadFn_t`
      (typedef 51-56) and `_WriteFn_t` (73-78): change return `size_t` ->
      `McciBootloaderDeviceI2cResult_t`, add `size_t *pnActual`. Rewrite the doc
      blocks (39-50 read, 58-72 write); delete the write's "@note There's currently
      no way to determine why fewer bytes were written" (69-72) -- now there is.
- [x] `mcci_bootloader_device_i2c_bus.h` -- methods struct references the Fn
      typedefs (41-42); no signature change, just confirm the type include resolves.

Device layer (wraps the bus, same change):

- [x] `mcci_bootloader_device_i2c_device_types.h` --
      `McciBootloaderDeviceI2cDevice_ReadFn_t` (50-55) and `_WriteFn_t` (71-75):
      same return/out-param change; rewrite doc (39-49, 57-70), drop the same
      stale "@note" (67-70).
- [x] `mcci_bootloader_device_i2c_device.h` -- methods struct (45-46); confirm
      includes only.

SoC implementation (`platform/soc/stm32l0/src/mccibootloader_stm32l0_i2c_bus.c`):

- [x] The local `McciBootloaderI2cBusStm32l0_Status_t` (41-51) mixes caller-facing
      results (`Done`/`TimeOut`/`ArbitrationLost`/`NackError`/`BusError`) with
      loop-control states (`Busy`/`Stopped`/`NotBusy`). Keep it internal for the
      loop, and translate to the abstract result at each return -- don't expose the
      SoC enum. Map: `Done`/`Stopped` (full count) -> `_OK`; `TimeOut` -> `_Timeout`;
      `ArbitrationLost` -> `_ArbitrationLost`; `NackError` -> `_Nack`; `BusError`
      -> `_BusError`.
- [x] `i2cBusRead` (333) and `i2cBusWrite` (427): match the new Fn typedef, set
      `*pnActual = nBuffer_orig - nBuffer` (if non-NULL), and return the mapped
      result instead of the byte count (returns at 424 and ~567).

Callers:

- [x] `driver/npm1300/` device driver (headers only today) -- write its register
      read/write wrappers, `createAndAttach`, and `initializeRegisters` to the new
      signature and propagate the result. Only future consumer of the device i2c
      API, so changing the API now costs nothing here.
- [x] `mccibootloaderboard_catena5230_systeminit.c` -- goes through the NPM1300
      driver, not the bus API directly, so it only changes if the NPM1300 API
      surfaces the new result.

## Platform

- [x] Implement `McciBootloaderPlatform_getMilliseconds()`. The STM32L0 I2C bus
      driver carries a temporary forward declaration
      (`platform/soc/stm32l0/src/mccibootloader_stm32l0_i2c_bus.c:58-61`) so it
      compiles; remove that stub once the platform provides the function.

## I2C bus driver loose ends

- [x] `McciBootloaderDeviceI2cBusStm32l0_attach()` is declared in
      `mcci_bootloader_device_i2c_bus_stm32l0.h` but not defined. Implement it, or
      confirm the NPM1300 `createAndAttach` path is what wires device->bus and drop
      the declaration.

## SPI: audit CS pins for NSS-as-GPIO (moved from punchlist-2ee6a11)

The hardware team did not know that routing a flash chip-select to a non-NSS pin
forces software NSS management. Every board SPI driver assumes hardware NSS today
(SSOE + SPE toggle). Check each one's CS pin against the part's AF table:

- ABZ (`catena_abz`): CS=PB12 = SPI2_NSS at AF0. Valid hardware NSS, no change.
- 1SJ (`catena_1sj`): CS=PA8, no NSS. Manual GPIO CS -- done.
- [ ] 51xx / 5082 (Model 5082, STM32L082) and any other new board: confirm the CS
      pin is a real SPI NSS pin before assuming hardware NSS; otherwise add manual
      GPIO CS.

(The Arduino SPI driver may handle GPIO CS on its own; out of scope here.)

## Remaining 5230 integration (see doc/plan-catena-51xx-52xx-bootloader-support.md)

- [x] PB10/PB11 as AF6 open-drain with pull-up, and the I2C2 pin/clock setup, in
      the 5230 board layer (initI2cBus takes no pin args).
- [x] NPM1300 device driver (`driver/npm1300/` is headers only:
      `createAndAttach`, `initializeRegisters`).
- [ ] 5230 `prepareForLaunch`: disable LOADSW2 before launch for micropower while
      keeping the PMIC's low-power init.
