/*
 * crc_hw_sample.c
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-03-22     qiyongzhong       first version
 */

#include <rtthread.h>
#include <crc_hw_sample.h>

#ifdef CRCLIB_USING_CRC_HW
#ifdef CRCLIB_USING_CRC_HW_SAMPLE

crc_hw_inst_t crc8_hw_sample_inst;

static int crc8_hw_sample_init(void)
{
    crc_hw_init(&crc8_hw_sample_inst, CRC8_HW_SAMPLE_POLY);
    return(0);
}
INIT_BOARD_EXPORT(crc8_hw_sample_init);

#ifdef CRCLIB_USING_CRC8
#if (CRC8_HW_SAMPLE_POLY == CRC8_POLY)
static void crc8_hw_test(void)
{
    u8 data[128];

    for (int i=0; i<sizeof(data); i++)
    {
        data[i] = 0x10 + i;
    }

    u8 crc8_rst = crc8_cal(data, sizeof(data));
    rt_kprintf("crc8_cal result = 0x%02X\n", crc8_rst);
    
    u8 crc8_hw_rst = CRC8_HW_SAMPLE_CAL(data, sizeof(data));
    rt_kprintf("crc8_hw_cal result = 0x%02X\n", crc8_hw_rst);

    if (crc8_rst == crc8_hw_rst)
    {
        rt_kprintf("crc8_hw_test is pass.\n");
    }   
}
MSH_CMD_EXPORT(crc8_hw_test, crc8 hardware functions test);
#endif
#endif

crc_hw_inst_t crc16_hw_sample_inst;

static int crc16_hw_sample_init(void)
{
    crc_hw_init(&crc16_hw_sample_inst, CRC16_HW_SAMPLE_POLY);
    return(0);
}
INIT_BOARD_EXPORT(crc16_hw_sample_init);

#ifdef CRCLIB_USING_CRC16
#if (CRC16_HW_SAMPLE_POLY == CRC16_POLY)
static void crc16_hw_test(void)
{
    u8 data[128];

    for (int i=0; i<sizeof(data); i++)
    {
        data[i] = 0x10 + i;
    }

    u16 crc16_rst = crc16_cal(data, sizeof(data));
    rt_kprintf("crc16_cal result = 0x%04X\n", crc16_rst);
    
    u16 crc16_hw_rst = CRC16_HW_SAMPLE_CAL(data, sizeof(data));
    rt_kprintf("crc16_hw_cal result = 0x%04X\n", crc16_hw_rst);

    if (crc16_rst == crc16_hw_rst)
    {
        rt_kprintf("crc16_hw_test is pass.\n");
    }   
}
MSH_CMD_EXPORT(crc16_hw_test, crc16 hardware functions test);
#endif
#endif

crc_hw_inst_t crc32_hw_sample_inst;

static int crc32_hw_sample_init(void)
{
    crc_hw_init(&crc32_hw_sample_inst, CRC32_HW_SAMPLE_POLY);
    return(0);
}
INIT_BOARD_EXPORT(crc32_hw_sample_init);

#ifdef CRCLIB_USING_CRC32
#if (CRC32_HW_SAMPLE_POLY == CRC32_POLY)
static void crc32_hw_test(void)
{
    u8 data[128];

    for (int i=0; i<sizeof(data); i++)
    {
        data[i] = 0x10 + i;
    }

    u32 crc32_rst = crc32_cal(data, sizeof(data));
    rt_kprintf("crc32_cal result = 0x%08X\n", crc32_rst);
    
    u32 crc32_hw_rst = CRC32_HW_SAMPLE_CAL(data, sizeof(data));
    rt_kprintf("crc32_hw_cal result = 0x%08X\n", crc32_hw_rst);

    if (crc32_rst == crc32_hw_rst)
    {
        rt_kprintf("crc32_hw_test is pass.\n");
    }   
}
MSH_CMD_EXPORT(crc32_hw_test, crc32 hardware functions test);
#endif
#endif

#endif
#endif

