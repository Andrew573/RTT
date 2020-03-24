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

#define OLED_ADDERSS 0x78

static void oled_thread_entry(void *parameter)
{
    rt_kprintf("this is oled thread\n");
    while(1)
    {
         rt_thread_mdelay(1000);
    }
}

int oled_sample()
{
    rt_thread_t oled_thread = rt_thread_create("oled1", oled_thread_entry,
                                RT_NULL, 1024, 25, 10);
    if(oled_thread != RT_NULL)
        rt_thread_startup(oled_thread);
    else
        return RT_ERROR;
    return RT_EOK;
}

