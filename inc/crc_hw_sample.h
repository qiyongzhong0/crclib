/*
 * crc_hw_sample.h
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-03-22     qiyongzhong       first version
 */

#ifndef __CRC_HW_SAMPLE_H__
#define __CRC_HW_SAMPLE_H__

#include <crc.h>

#ifdef CRCLIB_USING_CRC_HW
#ifdef CRCLIB_USING_CRC_HW_SAMPLE

#define CRC8_HW_SAMPLE_POLY         0x8C

extern crc_hw_inst_t crc8_hw_sample_inst;

#define CRC8_HW_SAMPLE_CYC_CAL(init, pd, len)   (u8)crc_hw_cyc_cal(&crc8_hw_sample_inst, init, pd, len)
#define CRC8_HW_SAMPLE_CAL(pd, len)             (u8)crc_hw_cal(&crc8_hw_sample_inst, pd, len)

#define CRC16_HW_SAMPLE_POLY        0xA001

extern crc_hw_inst_t crc16_hw_sample_inst;

#define CRC16_HW_SAMPLE_CYC_CAL(init, pd, len)  (u16)crc_hw_cyc_cal(&crc16_hw_sample_inst, init, pd, len)
#define CRC16_HW_SAMPLE_CAL(pd, len)            (u16)crc_hw_cal(&crc16_hw_sample_inst, pd, len)


#define CRC32_HW_SAMPLE_POLY        0xEDB88320

extern crc_hw_inst_t crc32_hw_sample_inst;

#define CRC32_HW_SAMPLE_CYC_CAL(init, pd, len)  crc_hw_cyc_cal(&crc32_hw_sample_inst, init, pd, len)
#define CRC32_HW_SAMPLE_CAL(pd, len)            crc_hw_cal(&crc32_hw_sample_inst, pd, len)

#endif
#endif
#endif

