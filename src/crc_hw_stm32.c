/*
 * crc_hw_stm32.h
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-03-21     qiyongzhong       first version
 */

#include "crc_hw_stm32.h"

#ifdef CRCLIB_USING_CRC_HW
#ifdef CHIP_FAMILY_STM32

#ifdef CHIP_SERIES_STM32F0
#include <stm32f0xx_ll_crc.h>
#endif
#ifdef CHIP_SERIES_STM32F1
#include <stm32f1xx_ll_crc.h>
#endif
#ifdef CHIP_SERIES_STM32F2
#include <stm32f2xx_ll_crc.h>
#endif
#ifdef CHIP_SERIES_STM32F4
#include <stm32f4xx_ll_crc.h>
#endif
#ifdef CHIP_SERIES_STM32F7
#include <stm32f7xx_ll_crc.h>
#endif
#ifdef CHIP_SERIES_STM32L0
#include <stm32l0xx_ll_crc.h>
#endif
#ifdef CHIP_SERIES_STM32L1
#include <stm32l1xx_ll_crc.h>
#endif
#ifdef CHIP_SERIES_STM32L2
#include <stm32l2xx_ll_crc.h>
#endif
#ifdef CHIP_SERIES_STM32L4
#include <stm32l4xx_ll_crc.h>
#endif
#ifdef CHIP_SERIES_STM32H7
#include <stm32h7xx_ll_crc.h>
#endif

static bool crc_is_busy = false;

void crc_hw_init(crc_hw_inst_t *hinst, u32 poly)
{
    if (poly <= 0xFF)
    {
        hinst->size = CRC_POLYLENGTH_8B;
        hinst->poly = (__RBIT(poly) >> 24);
    }
    else if (poly <= 0xFFFF)
    {
        hinst->size = CRC_POLYLENGTH_16B;
        hinst->poly = (__RBIT(poly) >> 16);
    }
    else
    {
        hinst->size = CRC_POLYLENGTH_32B;
        hinst->poly = __RBIT(poly);
    }
}

u32 crc_hw_cyc_cal(crc_hw_inst_t *hinst, u32 init_val, u8 *pdata, u32 len)
{
    while(crc_is_busy)CRC_RTOS_DELAY(1);
    crc_is_busy = true;
    
    __HAL_RCC_CRC_CLK_ENABLE();

    LL_CRC_SetInputDataReverseMode(CRC, LL_CRC_INDATA_REVERSE_BYTE);
    LL_CRC_SetOutputDataReverseMode(CRC, LL_CRC_OUTDATA_REVERSE_BIT);
    LL_CRC_SetPolynomialCoef(CRC, hinst->poly);
    LL_CRC_SetPolynomialSize(CRC, hinst->size);
    LL_CRC_SetInitialData(CRC, init_val);
    LL_CRC_ResetCRCCalculationUnit(CRC);
    
    for(int i=0; i<len; i++)
    {
        LL_CRC_FeedData8(CRC, pdata[i]);
    }
    u32 rst = LL_CRC_ReadData32(CRC);
    
    __HAL_RCC_CRC_CLK_DISABLE();
    crc_is_busy = false;
    
    return(rst);
}

u32 crc_hw_cal(crc_hw_inst_t *hinst, u8 *pdata, u32 len)
{
    return(crc_hw_cyc_cal(hinst, CRC_HW_INIT_VAL, pdata, len) ^ CRC_HW_INIT_VAL);
}

#endif
#endif
