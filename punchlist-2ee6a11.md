# Punch list: review of 2ee6a11 (Catena 1sj support)

Temporary file; delete when done.

## Functional

- [ ] `platform/board/mcci/catena_1sj/src/mccibootloaderboard_catena1sj_spi.c`
      Convert from ABZ SPI2 driver to 1SJ SPI1 (plan §7.1):
  - [x] GPIO pins. Correct map (verified against the 5230 schematic and the
      L082 datasheet AF table): SCK=PB3, MISO=PB4, MOSI=PB5, CS=PA8.
      PB3/PB4/PB5 are SPI1 SCK/MISO/MOSI at AF0, the reset default, so no AFRL/AFRH
      ("mux") write is needed -- same as the ABZ driver on PB12-15. The old
      PA4-PA7 list was just the SPI1 default-pin assumption; this board uses the
      port-B remap (still AF0) plus a GPIO chip-select. High speed and the SCK
      (PB3) pulldown are correct.
  - [x] Cut/paste error in the port-B MODER write fixed (PB4 was set to PB3 twice;
      PB4 had been left in input mode).
  - [x] Clock enable: `RCC_APB2ENR_SPI1EN` (replaces `RCC_APB1ENR_SPI2EN`)
  - [x] Reset: `RCC_APB2RSTR_SPI1RST` set/clear (replaces APB1RSTR SPI2RST)
  - [x] Register base: `MCCI_STM32L0_REG_SPI1` throughout (spiInit and spiTransfer)
  - [ ] **CS on PA8 is a plain GPIO, not hardware NSS.** PA8 has no SPI1_NSS
      alternate function (AF list is MCO / USB_CRS_SYNC / USART1_RTS / TSC /
      EVENTOUT). The only SPI1_NSS pins are PA4 and PA15, and the board wires PA4
      out to the D14/A0 header. The L0 has no SYSCFG pin remap for SPI, so there
      is no way to put NSS on PA8. The driver must drive PA8 by hand:
    - [ ] spiInit: configure PA8 as a GPIO **output** (`MCCI_STM32L0_GPIO_MODE_OUT`),
        not AF, and set it high (deselected). Keep the existing PA8 OSPEEDR-high and
        PUPDR-none writes.
    - [ ] spiInit: drop the `MCCI_STM32L0_SPI_CR2_SSOE` write. SSOE drives the
        hardware NSS pin (PA4/PA15), not PA8, so it does nothing useful here.
    - [ ] spiTransfer: assert CS by clearing PA8 (BRR) before clocking; when
        `fContinue` is false, set PA8 high (BSRR) to deselect, next to clearing SPE.
        The byte loop already waits for RXNE on the last byte, so deasserting after
        the loop is safe.
  - [ ] Doc comment at line ~69: pin list now says "PA8: nss AF0" -- PA8 is a GPIO
      chip-select, not an alternate function. Fix the annotation.
- [ ] `mccibootloaderboard_catena1sj_systeminit.c:96` -- also enable `IOPAEN`
      (CS is on PA8; only `IOPBEN` is enabled now)

## Cross-cutting: audit all SPI drivers for NSS-as-GPIO

The hardware team did not know that routing a flash chip-select to a non-NSS pin
forces software NSS management. Every board SPI driver assumes hardware NSS today
(SSOE + SPE toggle). Check each one's CS pin against the part's AF table:

- ABZ (`catena_abz`): CS=PB12 = SPI2_NSS at AF0. Valid hardware NSS, no change.
- 1SJ (`catena_1sj`): CS=PA8, no NSS. Needs manual GPIO CS (above).
- 51xx / 5082 (Model 5082, STM32L082) and any other new board: confirm the CS pin
  is a real SPI NSS pin before assuming hardware NSS; otherwise add manual GPIO CS.

(The Arduino SPI driver may handle GPIO CS on its own; out of scope here.)

## Stale dates

- [x] `mccibootloaderboard_catena1sj_systeminit.c:10` -- copyright 2021 -> 2026
- [x] `mccibootloaderboard_catena1sj_systeminit.c:19` -- "March 2021" -> 2026
- [x] `mccibootloaderboard_catena1sj_vectors.c:9` -- copyright 2021 -> 2026
- [x] `mccibootloaderboard_catena1sj_vectors.c:18` -- "March 2021" -> 2026

## Typos and stale comments

- [x] `mccibootloaderboard_catena1sj_annunciator.c:8` -- "Copyright notice:" -> "Copyright and License:"
- [x] `mccibootloaderboard_catena1sj_annunciator.c:106` -- "indiation" -> "indication"
- [x] `mccibootloaderboard_catena1sj_annunciator.c:114` -- "THis" -> "This"
- [x] `mccibootloaderboard_catena1sj_annunciator.c:114-116` -- stale note: says
      `Catena1sj_handleSysTick()` calls `McciBootloaderBoard_CatenaAbz_handleSysTick()`;
      it actually calls `McciBootloader_LED_handleSysTick()`
- [x] `mccibootloaderboard_catena1sj_systeminit.c:6` -- `McciBootloaderBoard_Catena1SJ_SystemInit()`
      -> `McciBootloaderBoard_Catena1sj_systemInit()` (case)
- [x] `mccibootloaderboard_catena1sj_systeminit.c:76` -- "We then then enable" -> "We then enable"
- [x] `mccibootloaderboard_catena1sj_systeminit.c:203` -- "teh" -> "the"

## Adjacent (pre-existing, separate commits)

- [x] `i/mcci_bootloader_led_annunciator.h:36` -- `McciBootloader_LED_Annuciator_t`
      misspelled (missing "n"); fix header (and struct tag at line 50) so the
      comment at `mccibootloaderboard_catena1sj_annunciator.c:72` is correct
- [x] `catena_abz/src/mccibootloaderboard_catenaabz_systeminit.c:76` -- same "then then" typo
- [x] `catena_abz/src/mccibootloaderboard_catenaabz_vectors.c:136` -- SVC handler doc says
      "immediately returns"; it handles the full request set (1sj version has correct doc)
