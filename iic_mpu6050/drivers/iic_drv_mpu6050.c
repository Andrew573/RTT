/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-03-29     Andrew       the first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DEVICE_ADD 0x68   //A0空接为0x68，接vcc为0x69

static struct rt_i2c_bus_device *i2c_bus = RT_NULL;

static rt_uint8_t iic_write_reg(rt_uint8_t reg, rt_uint8_t data)
{
    rt_uint8_t buf[2] = {reg, data};
    struct rt_i2c_msg msgs;
    //rt_uint8_t num = 0;

    msgs.addr = DEVICE_ADD;
    msgs.flags = RT_I2C_WR;
    msgs.buf = buf;
    msgs.len = 2;

    if(rt_i2c_transfer(i2c_bus, &msgs, 1) == 1)
        return RT_EOK;
    else {
        rt_kprintf("rt_i2c_transfer() failed\n");
        return RT_ERROR;
    }
/*
    num = rt_i2c_transfer(i2c_bus, &msgs, 1);
    rt_kprintf("num = %d\n", num);
*/
}

static rt_uint8_t iic_read_reg(rt_uint8_t reg, rt_uint8_t len, rt_uint8_t *buf)
{
    struct rt_i2c_msg msgs[2];

    msgs[0].addr = DEVICE_ADD;
    msgs[0].flags = RT_I2C_WR;
    msgs[0].buf = &reg;
    msgs[0].len = 1;

    msgs[1].addr = DEVICE_ADD;
    msgs[1].flags = RT_I2C_RD;
    msgs[1].buf = buf;
    msgs[1].len = len;

    if(rt_i2c_transfer(i2c_bus, msgs, 2))
        return RT_EOK;
    else
        return RT_ERROR;

}

rt_uint8_t mpu6050_init()
{
    rt_err_t reg = RT_EOK;

    i2c_bus = (struct rt_i2c_bus_device *)rt_device_find("iic_mpu");
    if(i2c_bus == RT_NULL)
    {
        rt_kprintf("not find device iic_mpu\n");
        return RT_ERROR;
    }
    else{
        rt_thread_mdelay(1000); //maybe can delete this delay

        reg |= iic_write_reg(0x6B, 0x00); //唤醒休眠模式
        reg |= iic_write_reg(0x19, 0x07); //采样率 1khz
        reg |= iic_write_reg(0x1A, 0x06); //低通滤波器设置
        reg |= iic_write_reg(0x1C, 0x00); //2G模式，不自检
        reg |= iic_write_reg(0x1b, 0x18); //自检及测量范围

        if(RT_ERROR == reg)
            return RT_ERROR;
        return RT_EOK;
    }
}

rt_uint8_t mpu6050_check()
{
    rt_uint8_t data = 0;

    if(iic_read_reg(0x75, 1, &data))
        return RT_ERROR;
    else {
        if(data == 0x68)
            rt_kprintf("MPU6050 check success\n");
        else
            rt_kprintf("MPU6050 check fail\n");
        return RT_EOK;
    }
}

void mpu6050_get_gyroscope(rt_uint16_t *x, rt_uint16_t *y, rt_uint16_t *z)  //陀螺仪
{
    rt_uint8_t buf[6], ret;

    ret = iic_read_reg(0x43, 6, buf);
    if(ret == RT_EOK)
    {
        *x = ((rt_uint16_t) buf[0]<<8) | buf[1];
        *y = ((rt_uint16_t) buf[2]<<8) | buf[3];
        *z = ((rt_uint16_t) buf[4]<<8) | buf[5];
    }
    else {
        rt_kprintf("get_gyroscope fail\n");
    }
}

void mpu6050_get_accelerometer(rt_uint16_t *x, rt_uint16_t *y, rt_uint16_t *z)  //角速度
{
    rt_uint8_t buf[6], ret;

    ret = iic_read_reg(0x3B, 6, buf);
    if(ret == RT_EOK)
    {
        *x = ((rt_uint16_t) buf[0]<<8) | buf[1];
        *y = ((rt_uint16_t) buf[2]<<8) | buf[3];
        *z = ((rt_uint16_t) buf[4]<<8) | buf[5];
    }
    else {
        rt_kprintf("get_accelerometer fail\n");
    }
}

void mpu6050_get_temperature(rt_uint16_t *t)  //温度
{
    rt_uint8_t buf[2], ret;
    float temp;
    rt_int16_t raw;

    ret = iic_read_reg(0x41, 2, buf);
    if(ret == RT_EOK)
    {
        raw = ((rt_uint16_t)buf[0] << 8) | buf[1];
        temp = 36.53 + ((double)raw)/340;
        *t = temp*100;
    }
    else {
        rt_kprintf("get_accelerometer fail\n");
    }
}
