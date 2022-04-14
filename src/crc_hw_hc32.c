/*
 * crc_hw_stm32.h
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-03-21     qiyongzhong       first version
 */

#include "crc_hw_hc32.h"

#ifdef CRCLIB_USING_CRC_HW
#ifdef CHIP_FAMILY_HC32

#define DBG_TAG "crc_hw_hc32"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#ifdef CHIP_NAME_HC32F460
#include <hc32f460.h>
#endif

#if defined(CHIP_NAME_HC32F460)
static bool crc_is_busy = false;

void crc_hw_init(crc_hw_inst_t *hinst, u32 poly)
{
    if (poly == 0x8408)//CRC16 only support poly = x16+x12+x5+1 (CCITT,ISO,HDLC,ITUX25,PPP-FCS)
    {
        hinst->size = (0<<1);
        hinst->poly = poly;
        return;
    }
    if (poly == 0xEDB88320)//CRC32 only support poly = x32+x26+x23+...+x2+x+1 (ZIP,RAR,IEEE,LAN/FDDI,PPP-FCS)
    {
        hinst->size = (1<<1);
        hinst->poly = poly;
        return;
    }
    LOG_E("The polynomial is not support. The polynomial must is 0x8408 or 0xEDB88320");
}

u32 crc_hw_cyc_cal(crc_hw_inst_t *hinst, u32 init_val, u8 *pdata, u32 len)
{
    while(crc_is_busy)CRC_RTOS_DELAY(1);
    crc_is_busy = true;

    PWC_Fcg0PeriphClockCmd(PWC_FCG0_PERIPH_CRC, Enable);

    M4_CRC->CR = (hinst->size | (1<<2) | (1<<3) | (0<<4));
    M4_CRC->RESLT = init_val;
    
    for(int i=0; i<len; i++)
    {
        *((u8 *)&(M4_CRC->DAT0)) = pdata[i];
    }
    u32 rst = M4_CRC->RESLT;

    PWC_Fcg0PeriphClockCmd(PWC_FCG0_PERIPH_CRC, Disable);
    crc_is_busy = false;
    
    return(rst);
}

u32 crc_hw_cal(crc_hw_inst_t *hinst, u8 *pdata, u32 len)
{
    return(crc_hw_cyc_cal(hinst, CRC_HW_INIT_VAL, pdata, len) ^ CRC_HW_INIT_VAL);
}

#endif
#endif
#endif
