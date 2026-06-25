# Punch list: review of 2ee6a11 (Catena 1sj support)

Temporary file; delete when done.

## Functional

- [ ] `platform/board/mcci/catena_1sj/src/mccibootloaderboard_catena1sj_spi.c`
      Convert from ABZ SPI2 driver to 1SJ SPI1 (plan §7.1):
  - [x] GPIO: PA4/PA5/PA6/PA7 AF0, high speed, PA5 pulldown (replaces PB12-PB15, PB13 pulldown)
      BUG(tmm@mcci.com): the above GPIOs are wrong, we're using PA8, PB3/PB4/PB5.
  - [x] Clock enable: `RCC_APB2ENR_SPI1EN` (replaces `RCC_APB1ENR_SPI2EN`)
  - [x] Reset: `RCC_APB2RSTR_SPI1RST` set/clear (replaces APB1RSTR SPI2RST)
  - [x] Register base: `MCCI_STM32L0_REG_SPI1` throughout (spiInit and spiTransfer)
  - [x] Doc comment at line 69: update pin list PB12-15 -> PA4-7, pulldown PB13 -> PA5
      BUG(tmm@mcci.com): see above.
- [ ] `mccibootloaderboard_catena1sj_systeminit.c:96` -- also enable `IOPAEN`
      (one SPI1 pins is on port A; only `IOPBEN` is enabled now)

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
