/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-03-24     Andrew       the first version
 */

#include <rtthread.h>
#include <rtdevice.h>

//#define USE_OLED
#define USE_MPU

#ifdef USE_OLED
#define DEVICE_ADDERSS 0x78
#endif

#ifdef USE_MPU
#define DEVICE_ADDERSS 0x68   //A0空为0x68,接vcc为0x69
#endif

static struct rt_i2c_bus_device *i2c_bus = RT_NULL;

static rt_err_t iic_write_reg(rt_uint8_t reg, rt_uint8_t data)
{
    rt_uint8_t buf1[2];
    struct rt_i2c_msg msgs;
    rt_uint8_t num1 = 0;

    msgs.addr = DEVICE_ADDERSS;
    msgs.flags = RT_I2C_WR;
    msgs.buf = buf1;
    msgs.len = 2;

    num1 = rt_i2c_transfer(i2c_bus, &msgs, 1);
    rt_kprintf("num1 = %d\n", num1);


    return 0;
}

rt_err_t mpu6050_write_reg(rt_uint8_t reg, rt_uint8_t data)
{
    struct rt_i2c_msg msgs;
    rt_uint8_t buf[2] = {reg, data};

    msgs.addr  = DEVICE_ADDERSS;    /* 从机地址 */
    msgs.flags = RT_I2C_WR;       /* 写标志 */
    msgs.buf   = buf;             /* 发送数据指针 */
    msgs.len   = 2;

    if (rt_i2c_transfer(i2c_bus, &msgs, 1) == 1)
    {
        rt_kprintf("transfer ok\n");
        return RT_EOK;
    }
    else
    {
        rt_kprintf("transfer fail\n");
        return -RT_ERROR;
    }
}

static rt_err_t iic_read_reg(rt_uint8_t reg, rt_uint8_t len, rt_uint8_t *buf)
{
    struct rt_i2c_msg msgs[2];
    rt_uint8_t num1 = 0;

    msgs[0].addr = DEVICE_ADDERSS;
    msgs[0].flags = RT_I2C_WR;
    msgs[0].buf = &reg;
    msgs[0].len = 1;

    msgs[1].addr = DEVICE_ADDERSS;
    msgs[1].flags = RT_I2C_RD;
    msgs[1].buf = buf;
    msgs[1].len = len;

    num1 = rt_i2c_transfer(i2c_bus, msgs, 2);
    rt_kprintf("num1 = %d\n", num1);
    return 0;
}


static void oled_thread_entry(void *parameter)
{
    rt_uint8_t data = 0;
    rt_kprintf("this is oled thread\n");

    rt_thread_mdelay(1000);

    mpu6050_write_reg(0x6B, 0x00);

    iic_write_reg(0x6B, 0x00); //唤醒休眠模式
    iic_write_reg(0x19, 0x07); //唤醒休眠模式
    iic_write_reg(0x1A, 0x06); //唤醒休眠模式
    iic_write_reg(0x1C, 0x00); //唤醒休眠模式
    iic_write_reg(0x1b, 0x18); //唤醒休眠模式

    iic_read_reg(0x75, 1, &data);

    rt_kprintf("data = %d\n", data);
    while(1)
    {
         rt_thread_mdelay(1000);
    }
}

int8_t oled_sample()
{
    i2c_bus = (struct rt_i2c_bus_device *)rt_device_find("iic1");
    if(i2c_bus == RT_NULL)
        rt_kprintf("can't find iic1\n");

    rt_thread_t oled_thread = rt_thread_create("oled1", oled_thread_entry,
                                RT_NULL, 1024, 25, 10);
    if(oled_thread != RT_NULL)
        rt_thread_startup(oled_thread);
    else
        return RT_ERROR;
    return RT_EOK;
}

