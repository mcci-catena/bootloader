/*

Module:	mccibootloaderboard_catenaabz_vectors.c

Function:
	Vectors for bootloader for STM32H7B3 boards

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	ChaeHee Won, MCCI Corporation	June 2021

*/

#include "mcci_bootloader.h"
#include "mcci_bootloader_stm32h7.h"
#include "mcci_bootloader_board_stm32h7b3.h"

/****************************************************************************\
|
|	Manifest constants & typedefs.
|
\****************************************************************************/

static void McciBootloaderBoard_Stm32h7b3_NotHandled(void);

static McciBootloaderPlatform_ARMv6M_SvcHandlerFn_t
McciBootloaderBoard_Stm32h7b3_SvcHandler;

/****************************************************************************\
|
|	Read-only data.
|
\****************************************************************************/

const McciBootloader_Stm32H7PageZero_t
gk_McciBootloader_CortexVectors =
	{
	.PageZero =
	    {
	    .CortexVectors.vectors =
		{
		[0] = /* stack pointer */	(uint32_t) &g_McciBootloader_StackTop,
		[1] = /* entry point */		(uint32_t) McciBootloader_main,
		[2] = /* NMI */			(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[3] = /* HardFault */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[4] = /* MemManage */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[5] = /* BusFault */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[6] = /* UsageFault */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[7] = /* reserved */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[8] = /* reserved */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[9] = /* reserved */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[10] = /* reserved */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[11] = /* SVCall */		(uint32_t) McciBootloaderBoard_Stm32h7b3_SvcHandler,
		[12] = /* DebugMon */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[13] = /* reserved */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[14] = /* PendSV */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[15] = /* SysTick */		(uint32_t) McciBootloaderBoard_Stm32h7b3_handleSysTick,
		/*
		|| External Interrupts
		*/
		[16] = /* WWDG */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[17] = /* PVD_PVM */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[18] = /* RTC_TAMP_STAMP */	(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[19] = /* RTC_WKUP */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[20] = /* FLASH */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[21] = /* RCC */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[22] = /* EXTI0 */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[23] = /* EXTI1 */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[24] = /* EXTI2 */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[25] = /* EXTI3 */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[26] = /* EXTI4 */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[27] = /* DMA1_Stream0 */	(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[28] = /* DMA1_Stream1 */	(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[29] = /* DMA1_Stream2 */	(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[30] = /* DMA1_Stream3 */	(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[31] = /* DMA1_Stream4 */	(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[32] = /* DMA1_Stream5 */	(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[33] = /* DMA1_Stream6 */	(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[34] = /* ADC */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[35] = /* FDCAN1_IT0 */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[36] = /* FDCAN2_IT0 */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[37] = /* FDCAN1_IT1 */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[38] = /* FDCAN2_IT1 */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[39] = /* EXTI9_5 */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[40] = /* TIM1_BRK */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[41] = /* TIM1_UP */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[42] = /* TIM1_TRG_COM */	(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[43] = /* TIM1_CC */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[44] = /* TIM2 */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[45] = /* TIM3 */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[46] = /* TIM4 */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[47] = /* I2C1_EV */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[48] = /* I2C1_ER */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[49] = /* I2C2_EV */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[50] = /* I2C2_ER */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[51] = /* SPI1 */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[52] = /* SPI2 */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[53] = /* USART1 */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[54] = /* USART2 */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[55] = /* USART3 */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[56] = /* EXTI15_10 */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[57] = /* RTC_Alarm */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[58] = /* DFSDM2 */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[59] = /* TIM8_BRK_TIM12 */	(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[60] = /* TIM8_UP_TIM13 */	(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[61] = /* TIM8_TRG_COM_TIM14 */	(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[62] = /* TIM8_CC */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[63] = /* DMA1_Stream7 */	(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[64] = /* FMC */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[65] = /* SDMMC1 */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[66] = /* TIM5 */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[67] = /* SPI3 */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[68] = /* UART4 */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[69] = /* UART5 */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[70] = /* TIM6_DAC */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[71] = /* TIM7 */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[72] = /* DMA2_Stream0 */	(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[73] = /* DMA2_Stream1 */	(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[74] = /* DMA2_Stream2 */	(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[75] = /* DMA2_Stream3 */	(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[76] = /* DMA2_Stream4 */	(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[77] = /* Reserved */		0,
		[78] = /* Reserved */		0,
		[79] = /* FDCAN_CAL */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[80] = /* DFSDM1_FLT4 */	(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[81] = /* DFSDM1_FLT5 */	(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[82] = /* DFSDM1_FLT6 */	(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[83] = /* DFSDM1_FLT7 */	(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[84] = /* DMA2_Stream5 */	(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[85] = /* DMA2_Stream6 */	(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[86] = /* DMA2_Stream7 */	(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[87] = /* USART6 */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[88] = /* I2C3_EV */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[89] = /* I2C3_ER */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[90] = /* OTG_HS_EP1_OUT */	(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[91] = /* OTG_HS_EP1_IN */	(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[92] = /* OTG_HS_WKUP */	(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[93] = /* OTG_HS */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[94] = /* DCMI_PSSI */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[95] = /* CRYP */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[96] = /* HASH_RNG */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[97] = /* FPU */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[98] = /* UART7 */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[99] = /* UART8 */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[100] = /* SPI4 */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[101] = /* SPI5 */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[102] = /* SPI6 */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[103] = /* SAI1 */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[104] = /* LTDC */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[105] = /* LTDC_ER */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[106] = /* DMA2D */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[107] = /* SAI2 */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[108] = /* OCTOSPI1 */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[109] = /* LPTIM1 */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[110] = /* CEC */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[111] = /* I2C4_EV */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[112] = /* I2C4_ER */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[113] = /* SPDIF_RX */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[114] = /* Reserved */		0,
		[115] = /* Reserved */		0,
		[116] = /* Reserved */		0,
		[117] = /* Reserved */		0,
		[118] = /* DMAMUX1_OVR */	(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[119] = /* Reserved */		0,
		[120] = /* Reserved */		0,
		[121] = /* Reserved */		0,
		[122] = /* Reserved */		0,
		[123] = /* Reserved */		0,
		[124] = /* Reserved */		0,
		[125] = /* Reserved */		0,
		[126] = /* DFSDM1_FLT0 */	(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[127] = /* DFSDM1_FLT1 */	(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[128] = /* DFSDM1_FLT2 */	(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[129] = /* DFSDM1_FLT3 */	(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[130] = /* Reserved */		0,
		[131] = /* SWPMI1 */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[132] = /* TIM15 */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[133] = /* TIM16 */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[134] = /* TIM17 */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[135] = /* MDIOS_WKUP */	(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[136] = /* MDIOS */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[137] = /* JPEG */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[138] = /* MDMA */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[139] = /* Reserved */		0,
		[140] = /* SDMMC2 */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[141] = /* HSEM1 */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[142] = /* Reserved */		0,
		[143] = /* DAC2 */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[144] = /* DMAMUX2_OVR */	(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[145] = /* BDMA2_Channel0 */	(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[146] = /* BDMA2_Channel1 */	(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[147] = /* BDMA2_Channel2 */	(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[148] = /* BDMA2_Channel3 */	(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[149] = /* BDMA2_Channel4 */	(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[150] = /* BDMA2_Channel5 */	(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[151] = /* BDMA2_Channel6 */	(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[152] = /* BDMA2_Channel7 */	(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[153] = /* COMP */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[154] = /* LPTIM2 */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[155] = /* LPTIM3 */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[156] = /* UART9 */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[157] = /* UART10 */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[158] = /* LPUART1 */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[159] = /* Reserved */		0,
		[160] = /* CRS */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[161] = /* ECC */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[162] = /* Reserved */		0,
		[163] = /* DTS */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[164] = /* Reserved */		0,
		[165] = /* WAKEUP_PIN */	(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[166] = /* OCTOSPI2 */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[167] = /* OTFDEC1 */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[168] = /* OTFDEC2 */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[169] = /* GFXMMU */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		[170] = /* BDMA1 */		(uint32_t) McciBootloaderBoard_Stm32h7b3_NotHandled,
		},
	    .AppInfo =
		{
		.magic = MCCI_BOOTLOADER_APP_INFO_MAGIC,
		.size = sizeof(McciBootloader_AppInfo_t),
		.targetAddress = (uint32_t) &gk_McciBootloader_CortexVectors,
		.imagesize = (uint32_t) &gk_McciBootloader_ImageSize,
		.authsize = sizeof(McciBootloader_SignatureBlock_t),
		}
	    }
	};

// instantiate the signature block.
const McciBootloader_SignatureBlock_t
gk_McciBootloader_SignatureBlock;


/****************************************************************************\
|
|	Variables.
|
\****************************************************************************/


/****************************************************************************\
|
|	Code
|
\****************************************************************************/

/// \brief interrupt not handled; loop.
static void
McciBootloaderBoard_Stm32h7b3_NotHandled(void)
	{
	while (true)
		;
	}

/// \brief SVC handler -- immediately returns
static void
McciBootloaderBoard_Stm32h7b3_SvcHandler(
	McciBootloaderPlatform_ARMv6M_SvcRq_t svcRequest,
	McciBootloaderPlatform_ARMv6M_SvcError_t *pErrorCode,
	uint32_t arg1,
	uint32_t arg2
	)
	{
	McciBootloaderPlatform_ARMv6M_SvcError_t err;

	err = McciBootloaderPlatform_SvcError_OK;

	switch (svcRequest)
		{
	case McciBootloaderPlatform_ARMv6M_SvcRq_GetUpdatePointer:
		{
		uint32_t ** const pResult = (uint32_t **)arg1;
		McciBootloaderBoard_Stm32h7b3_Request_t * const pRequest =
			McciBootloaderBoard_Stm32h7b3_getRequestPointer();

		/* return pointer to user */
		if (pResult != NULL)
			*pResult = &pRequest->fUpdateRequest;
		else
			err = McciBootloaderPlatform_SvcError_InvalidParameter;
		}
		break;

	case McciBootloaderPlatform_ARMv6M_SvcRq_HashInit:
		{
		mcci_tweetnacl_sha512_t * const pHash = (void *)arg1;

		mcci_tweetnacl_hashblocks_sha512_init(pHash);
		}
		break;

	case McciBootloaderPlatform_ARMv6M_SvcRq_HashBlocks:
		{
		McciBootloaderPlatform_ARMv6M_SvcRq_HashBlocks_Arg_t * const
			pArg = (void *)arg1;

		if (arg1 == 0 || (arg1 & 3) != 0)
			err = McciBootloaderPlatform_SvcError_InvalidParameter;
		else
			{
			mcci_tweetnacl_sha512_t * const pHash = pArg->pHash;
			pArg->nMessage = mcci_tweetnacl_hashblocks_sha512(
				pHash,
				pArg->pMessage,
				pArg->nMessage
				);
			}
		}
		break;

	case McciBootloaderPlatform_ARMv6M_SvcRq_HashFinish:
		{
		McciBootloaderPlatform_ARMv6M_SvcRq_HashFinish_Arg_t * const
			pArg = (void *)arg1;

		if (arg1 == 0 || (arg1 & 3) != 0)
			err = McciBootloaderPlatform_SvcError_InvalidParameter;
		else
			{
			mcci_tweetnacl_sha512_t * const pHash = pArg->pHash;
			mcci_tweetnacl_hashblocks_sha512_finish(
				pHash,
				pArg->pMessage,
				pArg->nMessage,
				pArg->nOverall
				);
			}
		}
		break;

	case McciBootloaderPlatform_ARMv6M_SvcRq_Verify64:
		{
		const mcci_tweetnacl_sha512_t * const
			pArg1 = (void *)arg1;
		const mcci_tweetnacl_sha512_t * const
			pArg2 = (void *)arg2;

		mcci_tweetnacl_result_t const r = mcci_tweetnacl_verify_64(pArg1->bytes, pArg2->bytes);
		err = mcci_tweetnacl_result_is_success(r)
			? McciBootloaderPlatform_SvcError_OK
			: McciBootloaderPlatform_SvcError_VerifyFailure
			;
		}
		break;

	default:
		err = McciBootloaderPlatform_SvcError_Unclaimed;
		break;
		}

	// return result
	*pErrorCode = err;
	}

/**** end of mccibootloaderboard_catenaabz_vectors.c ****/
