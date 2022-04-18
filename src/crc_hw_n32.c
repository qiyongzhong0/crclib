/*
 * crc_hw_n32.h
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-04-18     qiyongzhong       first version
 */

#include "crc_hw_n32.h"

#ifdef CRCLIB_USING_CRC_HW
#ifdef CHIP_FAMILY_N32

#define DBG_TAG "crc_hw_n32"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>
#include <string.h>
#if (defined(CHIP_SERIES_N32G452) || defined(CHIP_SERIES_N32G455) || defined(CHIP_SERIES_N32G457))
#include <n32g45x.h>
#endif

#if (defined(CHIP_SERIES_N32G452) || defined(CHIP_SERIES_N32G455) || defined(CHIP_SERIES_N32G457))

static bool crc16_is_busy = false;
static bool crc32_is_busy = false;

void crc_hw_init(crc_hw_inst_t *hinst, u32 poly)
{
    if (poly == 0xA001)//CRC16 only support poly = x16+x15+x2+1 (IBM,SDLC)
    {
        hinst->size = 16;
        hinst->poly = poly;
        return;
    }
    if (poly == 0xEDB88320)//CRC32 only support poly = x32+x26+x23+...+x2+x+1 (ZIP,RAR,IEEE,LAN/FDDI,PPP-FCS)
    {
        hinst->size = 32;
        hinst->poly = poly;
        return;
    }
    LOG_E("The polynomial is not support. The polynomial must is 0xA001 or 0xEDB88320");
}

u32 crc_hw_cyc_cal(crc_hw_inst_t *hinst, u32 init_val, u8 *pdata, u32 len)
{
    u32 rst;

    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_CRC, ENABLE);

    if (hinst->size == 16)
    {
        while(crc16_is_busy)CRC_RTOS_DELAY(1);
        crc16_is_busy = true;

        CRC->CRC16CTRL = ((1<<1) | (1<<2));
        CRC->CRC16D = init_val;
        for(int i=0; i<len; i++)
        {
            CRC->CRC16DAT = pdata[i];
        }
        rst = (__RBIT(CRC->CRC16D) >> 16);

        crc16_is_busy = false;
    }
    else
    {
        if ((len % 4) != 0)
        {
            LOG_E("the length must be a multiple of 4.");
            return(-1);
        }

        while(crc32_is_busy)CRC_RTOS_DELAY(1);
        crc32_is_busy = true;

        if (init_val == 0xFFFFFFFF)
        {
            CRC->CRC32CTRL = (1<<0);
        }
        u32 td32;
        for(int i=0; i<len/4; i++)
        {
            memcpy((u8 *)&td32, (u8 *)pdata, 4);
            CRC->CRC32DAT = __RBIT(td32);
            pdata += 4;
        }
        rst = __RBIT(CRC->CRC32DAT);

        crc32_is_busy = false;
    }

    return(rst);
}

u32 crc_hw_cal(crc_hw_inst_t *hinst, u8 *pdata, u32 len)
{
    return(crc_hw_cyc_cal(hinst, CRC_HW_INIT_VAL, pdata, len) ^ CRC_HW_INIT_VAL);
}

#endif
#endif
#endif
