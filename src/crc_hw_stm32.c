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

    CRC_HandleTypeDef crc_handle;
    crc_handle.Instance = CRC;
    crc_handle.InputDataFormat = CRC_INPUTDATA_FORMAT_BYTES;
    crc_handle.Init.DefaultPolynomialUse = DEFAULT_POLYNOMIAL_DISABLE;
    crc_handle.Init.DefaultInitValueUse = DEFAULT_INIT_VALUE_DISABLE;
    crc_handle.Init.GeneratingPolynomial = hinst->poly;
    crc_handle.Init.CRCLength = hinst->size;
    crc_handle.Init.InitValue = init_val;
    crc_handle.Init.InputDataInversionMode = CRC_INPUTDATA_INVERSION_BYTE;
    crc_handle.Init.OutputDataInversionMode = CRC_OUTPUTDATA_INVERSION_ENABLE;
    HAL_CRC_Init(&crc_handle);
    
    u32 rst = HAL_CRC_Calculate(&crc_handle, (u32 *)pdata, len);
    
    HAL_CRC_DeInit(&crc_handle);
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
