/*
 * crc16.h
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-07-02     qiyongzhong       first version
 */

#ifndef __CRC16_H__
#define __CRC16_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "crc_cfg.h"
#include "typedef.h"

#ifdef CRCLIB_USING_CRC16

#if (!defined(CRC16_USING_CONST_TABLE) ||                                      \
     ((CRC16_POLY != 0xA001) && (CRC16_POLY != 0x8408)))
/*
 * @brief   cyclic initialize crc table
 * @param   none
 * @retval  none
 */
void crc16_table_init(void);
#endif

/*
 * @brief   cyclic calculation crc check value
 * @param   init_val    - initial value
 * @param   pdata       - datas pointer
 * @param   len         - datas len
 * @retval  calculated result
 */
uint16_t crc16_cyc_cal(uint16_t init_val, uint8_t *pdata, uint32_t len);

/*
 * @brief   calculation crc check value, initial is 0xFFFF
 * @param   pdata       - datas pointer
 * @param   len         - datas len
 * @retval  calculated result
 */
uint16_t crc16_cal(uint8_t *pdata, uint32_t len);

#endif
#ifdef __cplusplus
}
#endif
#endif
