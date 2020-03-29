/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-03-29     Andrew       the first version
 */
#ifndef DRIVERS_IIC_DRV_MPU6050_H_
#define DRIVERS_IIC_DONG_H_

rt_uint8_t mpu6050_init();
rt_uint8_t mpu6050_check();
void mpu6050_get_gyroscope(rt_uint16_t *x, rt_uint16_t *y, rt_uint16_t *z);
void mpu6050_get_accelerometer(rt_uint16_t *x, rt_uint16_t *y, rt_uint16_t *z);
void mpu6050_get_temperature(rt_uint16_t *t);

#endif /* DRIVERS_IIC_DRV_MPU6050_H_ */
