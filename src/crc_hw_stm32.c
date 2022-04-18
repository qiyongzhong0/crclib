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

    CRC->POL = hinst->poly;
    CRC->INIT = init_val;
    CRC->CR = ((1<<0) | (hinst->size) | (1<<5) | (1<<7));

    for(int i=0; i<len; i++)
    {
        *((u8 *)&(CRC->DR)) = pdata[i];
    }
    u32 rst = CRC->DR;
    
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
