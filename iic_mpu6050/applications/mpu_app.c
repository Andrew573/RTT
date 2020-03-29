/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-03-29     Andrew       the first version
 */

#include "mpu_app.h"

static void mpu_thread_entry(void *para)
{
    rt_kprintf("this is mpu thread\n");

    if(RT_EOK == mpu6050_init())
    {
        rt_kprintf("mpu6050 init success\n");
    }
    else
        rt_kprintf("mpu6050 init fail\n");
    mpu6050_check();
}

rt_err_t mpu_sample()
{
    rt_err_t ret = RT_EOK;

    rt_thread_t thread_mpu = rt_thread_create("mpu",
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
