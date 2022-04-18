/*
 * crc_hw_n32.h
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-04-18     qiyongzhong       first version
 */

#ifndef __CRC_HW_N32_H__
#define __CRC_HW_N32_H__

#include "typedef.h"
#include "crc_cfg.h"

#ifdef CRCLIB_USING_CRC_HW

#include <board.h>

#ifdef CHIP_FAMILY_N32

#define CRC_HW_INIT_VAL     0xFFFFFFFF
#define CRC_RTOS_DELAY(x)   rt_thread_delay(x)

typedef struct{
    u32 size;
    u32 poly;
}crc_hw_inst_t;

/* 
 * @brief   initialize crc instance
 * @param   hinst       - instance handle
 * @param   poly        - polynomial of crc
 * @retval  none
 */
void crc_hw_init(crc_hw_inst_t *hinst, u32 poly);

/* 
 * @brief   cyclic calculation crc check value
 * @param   hinst       - instance handle
 * @param   init_val    - initial value
 * @param   pdata       - datas pointer
 * @param   len         - datas len
 * @retval  calculated result 
 */
u32 crc_hw_cyc_cal(crc_hw_inst_t *hinst, u32 init_val, u8 *pdata, u32 len);

/* 
 * @brief   calculation crc check value, initial is CRC_HW_INIT_VAL
 * @param   hinst       - instance handle
 * @param   pdata       - datas pointer
 * @param   len         - datas len
 * @retval  calculated result 
 */
u32 crc_hw_cal(crc_hw_inst_t *hinst, u8 *pdata, u32 len);

#endif
#endif
#endif

