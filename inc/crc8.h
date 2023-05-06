/*
 * crc8.h
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-07-02     qiyongzhong       first version
 */

#ifndef __CRC8_H__
#define __CRC8_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "crc_cfg.h"
#include <typedef.h>

#ifdef CRCLIB_USING_CRC8

#if (!defined(CRC8_USING_CONST_TABLE) ||                                       \
     ((CRC8_POLY != 0x8C) && (CRC8_POLY != 0xD9)))
/*
 * @brief   cyclic initialize crc table
 * @param   none
 * @retval  none
 */
void crc8_table_init(void);
#endif

/*
 * @brief   cyclic calculation crc check value
 * @param   init_val    - initial value
 * @param   pdata       - datas pointer
 * @param   len         - datas len
 * @retval  calculated result
 */
uint8_t crc8_cyc_cal(uint8_t init_val, uint8_t *pdata, uint32_t len);

/*
 * @brief   calculation crc check value, initial is CRC8_INIT_VOL
 * @param   pdata       - datas pointer
 * @param   len         - datas len
 * @retval  calculated result
 */
uint8_t crc8_cal(uint8_t *pdata, uint32_t len);

#endif
#ifdef __cplusplus
}
#endif
#endif
