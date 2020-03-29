#include <applications/oled_app.h>
/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-03-29     Andrew       the first version
 */


static void mpu_thread_entry(void *para)
{
    rt_uint16_t x = 0, y = 0, z = 0;
    rt_kprintf("this is mpu thread\n");

    if(RT_EOK == mpu6050_init())
    {
        rt_kprintf("mpu6050 init success\n");
    }
    else
        rt_kprintf("mpu6050 init fail\n");
    mpu6050_check();
    while(1)
    {
        mpu6050_get_gyroscope(&x, &y, &z);
        rt_kprintf("gx=%d, gy=%d, gz=%d\n", x,y,z);
        mpu6050_get_accelerometer(&x, &y, &z);
        rt_kprintf("ax=%d, ay=%d, az=%d\n", x,y,z);
        mpu6050_get_temperature(&x);
        rt_kprintf("temp=%d\n", x);
        rt_thread_mdelay(1000);
    }
}

rt_err_t mpu_sample()
{
    rt_err_t ret = RT_EOK;

    rt_thread_t thread_mpu = rt_thread_create("oled",
                                               mpu_thread_entry,
                                               RT_NULL,
                                               1024,
                                               25,
                                               10);
    if(thread_mpu != RT_NULL)
    {
        rt_thread_startup(thread_mpu);
        return ret;
    }
    else
        return ret = RT_ERROR;


}
