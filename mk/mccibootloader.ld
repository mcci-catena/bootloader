/*

Module: mccibootloader.ld

Function:
        Input linker script for MCCI bootloader for STM32

Copyright notice:
        This file copyright (C) 2017, 2020 by

                MCCI Corporation
                3520 Krums Corners Road
                Ithaca, NY  14850

        An unpublished work.  All rights reserved.

        See accompanying LICENSE file for license information.

Author:
        Terry Moore, MCCI Corporation	July 2020

*/

ENTRY(McciBootloader_Main)

/* ram base */
g_McciBootloader_RamBase        = 0x20000000;
gk_McciBootloader_RamSize       = 20K;
g_McciBootloader_FlashBase      = 0x08000000;
gk_McciBootloader_ImageSize     = 192K;

/* initial stack pointer: top of RAM */
g_McciBootloader_StackTop = g_McciBootloader_RamBase + gk_McciBootloader_RamSize;

/* where things are (for the client) */
gk_McciBootloader_SelfBase = .;
gk_McciBootloader_SelfTop = gk_McciBootloader_SelfBase + gk_McciBootloader_ImageSize;

/* the memory areas */
MEMORY
        {
        FLASH (rx)      : ORIGIN = g_McciBootloader_FlashBase, LENGTH = gk_McciBootloader_ImageSize
        RAM (xrw)       : ORIGIN = g_McciBootloader_RamBase, LENGTH = gk_McciBootloader_RamSize
        }

/* declare how the output sections should be construted and mapped to memory */
SECTIONS
        {
        /* the header section comes first (with the ISR vectors) */
        .McciBootloader_Header :
                {
                . = ALIGN(4);

                /* there may not be any references to the names, so don't let relaxation toss this */
                KEEP(*(.McciBootloader_Vectors))
                KEEP(*(.McciBootloader_Header))
                . = ALIGN(4);
                } > FLASH

        /* then comes the code */
        .text ALIGN(4) :
                {
                . = ALIGN(4);
                *(.text*)       /* code sections that haven't been per-function-ized */
                *(.rodata*)     /* read-only data */

                /* no constructors, destructors, etc. The reset handler is responsible for everything */
                } > FLASH

        /* capture all the .data segments; we'll assert below. */
        .data :
                {
                *(.data*)       /* all the data sections */
                } > FLASH

        /* The RAM data (if any) */
        .bss :
                {
                . = ALIGN(4);
                g_McciBootloader_BssStart = .;
                *(.bss*)
                . = ALIGN(4);
                g_McciBootloader_BssEnd = .;
                } > RAM
        }

ASSERT(SIZEOF(.data) == 0, "Don't use initialized data in boot-loaders!");
