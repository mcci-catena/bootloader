/*

Module: mccibootloader.ld

Function:
        Input linker script for MCCI bootloader for STM32H7B3

Copyright notice:
        This file copyright (C) 2021 by

                MCCI Corporation
                3520 Krums Corners Road
                Ithaca, NY  14850

        An unpublished work.  All rights reserved.

        See accompanying LICENSE file for license information.

Author:
	ChaeHee Won, MCCI Corporation	June 2021

*/

ENTRY(McciBootloader_main)

/* the gross memory characteristics */
g_McciBootloader_SocRamBase     = 0x20000000;
g_McciBootloader_SocRamSize     = 128K;
g_McciBootloader_SocRamTop      = g_McciBootloader_SocRamBase + g_McciBootloader_SocRamSize;

g_McciBootloader_AxiSramBase     = 0x24000000;
g_McciBootloader_AxiSramSize     = 1M;
g_McciBootloader_AxiSramTop      = g_McciBootloader_AxiSramBase + g_McciBootloader_AxiSramSize;

g_McciBootloader_AhbSramBase     = 0x30000000;
g_McciBootloader_AhbSramSize     = 128K;
g_McciBootloader_AhbSramTop      = g_McciBootloader_AhbSramBase + g_McciBootloader_AhbSramSize;

gk_McciBootloader_FlashBase     = 0x08000000;
gk_McciBootloader_FlashSize     = 2M;

g_McciBootloader_SocOtpBase     = 0x08FFF000;
gk_McciBootloader_SocOtpSize    = 1K;

/* size of boot loader (8K * 4 sector) */
gk_McciBootloader_BootSize      = 32K;
/* size of boot request image (8K * 1 sector) */
gk_McciBootloader_RequestSize   = 8K;
/* size of mfg page (8K * 1 sector) */
gk_McciBootloader_MfgSize       = 8K;

/* size of app */
gk_McciBootloader_AppSize       = 512K;

/* initial stack pointer: top of RAM */
g_McciBootloader_StackTop       = g_McciBootloader_SocRamTop;
g_McciBootloader_StackSize      = 4K;
g_McciBootloader_StackBase      = g_McciBootloader_SocRamTop - g_McciBootloader_StackSize;

/* size and base of bootlooader's ram */
gk_McciBootloader_WorkingRamSize = 8K;
g_McciBootloader_WorkingRamBase = g_McciBootloader_StackBase - gk_McciBootloader_WorkingRamSize;

/* where things are */
gk_McciBootloader_BootBase      = gk_McciBootloader_FlashBase;
gk_McciBootloader_BootTop       = gk_McciBootloader_BootBase + gk_McciBootloader_BootSize;
gk_McciBootloader_AppBase       = gk_McciBootloader_BootTop;
gk_McciBootloader_AppTop        = gk_McciBootloader_AppBase + gk_McciBootloader_AppSize;

gk_McciBootloader_RequestBase   = gk_McciBootloader_AppTop;
gk_McciBootloader_RequestTop    = gk_McciBootloader_RequestBase + gk_McciBootloader_RequestSize;
gk_McciBootloader_MfgBase       = gk_McciBootloader_RequestTop;
gk_McciBootloader_MfgTop        = gk_McciBootloader_MfgBase + gk_McciBootloader_MfgSize;

gk_McciBootloader_UpdateBase    = gk_McciBootloader_FlashBase + 1M + 1K;
gk_McciBootloader_FallbackBase  = gk_McciBootloader_FlashBase + 1M + 512K;

/* the memory areas */
MEMORY
        {
        FLASH (rx)      : ORIGIN = gk_McciBootloader_BootBase,
                          LENGTH = gk_McciBootloader_BootSize
        EEPROM (rw)     : ORIGIN = g_McciBootloader_SocOtpBase,
                          LENGTH = gk_McciBootloader_SocOtpSize
        RAM (xrw)       : ORIGIN = g_McciBootloader_WorkingRamBase,
                          LENGTH = gk_McciBootloader_WorkingRamSize
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
                *(.text)        /* code sections that haven't been per-function-ized */
                *(.text*)       /* code sections that have been per-function-ized */
                . = ALIGN(4);
                *(.rodata)      /* read-only data */
                *(.rodata*)     /* read-only data */
                . = ALIGN(4);

                /* no constructors, destructors, etc. The reset handler is responsible for everything */
                } > FLASH

        /* the EEPROM (if any) */
        .eeprom :
                {
                . = ALIGN(4);   /* dword align */
                *(.eeprom)      /* all the EEPROM sections */
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
                *(.data)        /* in case not compiling with -ffunction-section */
                *(.data*)       /* all the data sections */
                *(.RamFunc)     /* code that runs from RAM */
                *(.RamFunc*)    /* code that runs from RAM */
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
                *(.bss)
                *(.bss*)
                *(COMMON)
                . = ALIGN(4);
                g_McciBootloader_BssTop = .;
                } > RAM
        }

/* end of script */