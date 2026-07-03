# Punch list: I2C bus driver and portable-API follow-ups

Temporary file; delete when done.

## Portable I2C API

- [ ] Add an error/status return to the portable I2C read/write API
      (`McciBootloaderDeviceI2cBus_ReadFn_t` / `WriteFn_t` and the device-layer
      equivalents in `driver/i2c/i/`). Today they return bytes transferred
      (`nBuffer_orig - nBuffer`). A zero-length probe returns 0 whether the device
      ACKed or NACKed, so presence can't be reported, and callers can't tell
      timeout / arb-loss / NACK / bus-error apart. The STM32L0 driver already
      tracks all of these in its `..._Status_t` enum -- surface it. Cheap to add
      now, annoying to thread through later.

## Platform

- [ ] Implement `McciBootloaderPlatform_getMilliseconds()`. The STM32L0 I2C bus
      driver carries a temporary forward declaration
      (`platform/soc/stm32l0/src/mccibootloader_stm32l0_i2c_bus.c:58-61`) so it
      compiles; remove that stub once the platform provides the function.

## I2C bus driver loose ends

- [ ] `McciBootloaderDeviceI2cBusStm32l0_attach()` is declared in
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

- [ ] PB10/PB11 as AF6 open-drain with pull-up, and the I2C2 pin/clock setup, in
      the 5230 board layer (initI2cBus takes no pin args).
- [ ] NPM1300 device driver (`driver/npm1300/` is headers only:
      `createAndAttach`, `initializeRegisters`).
- [ ] 5230 `prepareForLaunch`: disable LOADSW2 before launch for micropower while
      keeping the PMIC's low-power init.
