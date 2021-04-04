/*

Module: mccibootloader.ld

Function:
        Input linker script for MCCI bootloader for STM32

Copyright notice:
        This file copyright (C) 2017, 2020, 2021 by

                MCCI Corporation
                3520 Krums Corners Road
                Ithaca, NY  14850

        An unpublished work.  All rights reserved.

        See accompanying LICENSE file for license information.

Author:
        Terry Moore, MCCI Corporation	July 2020

*/

ENTRY(McciBootloader_main)

/* the gross memory characteristics */
g_McciBootloader_RamBase        = 0x20000000;
gk_McciBootloader_RamSize       = 20K;
gk_McciBootloader_FlashBase     = 0x08000000;
gk_McciBootloader_FlashSize     = 192K;
g_McciBootloader_SocEepromBase  = 0x08080000;
gk_McciBootloader_SocEepromSize  = 6K;

/* size of boot loader */
gk_McciBootloader_BootSize      = 20K;
/* size of mfg page */
gk_McciBootloader_MfgSize       = 4K;
/* size of app */
gk_McciBootloader_AppSize       = gk_McciBootloader_FlashSize - (gk_McciBootloader_BootSize + gk_McciBootloader_MfgSize);
/* bootloader Eeprom */
gk_McciBootloader_BootEepromSize  = 256;
g_McciBootloader_BootEepromBase  = g_McciBootloader_SocEepromBase
                                 + gk_McciBootloader_SocEepromSize
                                 - gk_McciBootloader_BootEepromSize
                                 ;
g_McciBootloader_BootEepromTop   = g_McciBootloader_BootEepromBase + gk_McciBootloader_BootEepromSize;

/* initial stack pointer: top of RAM */
g_McciBootloader_StackTop       = g_McciBootloader_RamBase + gk_McciBootloader_RamSize;
g_McciBootloader_RamTop         = g_McciBootloader_RamBase + gk_McciBootloader_RamSize;

/* where things are */
gk_McciBootloader_BootBase      = gk_McciBootloader_FlashBase;
gk_McciBootloader_BootTop       = gk_McciBootloader_BootBase + gk_McciBootloader_BootSize;
gk_McciBootloader_AppBase       = gk_McciBootloader_BootTop;
gk_McciBootloader_AppTop        = gk_McciBootloader_AppBase + gk_McciBootloader_AppSize;
gk_McciBootloader_MfgBase       = gk_McciBootloader_AppTop;
gk_McciBootloader_MfgTop        = gk_McciBootloader_MfgBase + gk_McciBootloader_MfgSize;

/* the memory areas */
MEMORY
        {
        FLASH (rx)      : ORIGIN = gk_McciBootloader_BootBase,
                          LENGTH = gk_McciBootloader_BootSize
        EEPROM (rw)     : ORIGIN = g_McciBootloader_BootEepromBase,
                          LENGTH = gk_McciBootloader_BootEepromSize
        RAM (xrw)       : ORIGIN = g_McciBootloader_RamBase,
                          LENGTH = gk_McciBootloader_RamSize
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
        .text :
                {
                . = ALIGN(4);
                *(.text*)       /* code sections that haven't been per-function-ized */
                . = ALIGN(4);
                *(.rodata*)     /* read-only data */
                . = ALIGN(4);

                /* no constructors, destructors, etc. The reset handler is responsible for everything */
                } > FLASH

        /* the EEPROM (if any) */
        .eeprom :
                {
                . = ALIGN(4);   /* dword align */
                *(.eeprom*)     /* all the EEPROM sections */
                . = ALIGN(4);   /* dword-align the tail */
                } > EEPROM

        /* capture all the .data segments. */
        . = ALIGN(4);
        gk_McciBootloader_DataImageBase = LOADADDR(.data);
        .data  :
                {
                . = ALIGN(4);   /* dword-align */
                g_McciBootloader_DataBase = .;
                *(.data*)       /* all the data sections */
                *(.RamFunc)     /* code that runs from RAM */
                . = ALIGN(4);   /* dword-align the tail */
                g_McciBootloader_DataTop = .;
                } >RAM AT> FLASH

        /* insert the application signature block */
        .McciBootloader_Signature :
                {
                gk_McciBootloader_ImageSize = . - gk_McciBootloader_BootBase;
                KEEP(*(.McciBootloader_Signature))
                } > FLASH

        /* The RAM data (if any) */
         . = ALIGN(4);
       .bss :
                {
                . = ALIGN(4);
                g_McciBootloader_BssBase = .;
                *(.bss*)
                . = ALIGN(4);
                g_McciBootloader_BssTop = .;
                } > RAM
        }


/* end of script */