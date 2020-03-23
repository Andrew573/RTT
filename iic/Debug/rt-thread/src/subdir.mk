################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../rt-thread/src/clock.c \
../rt-thread/src/components.c \
../rt-thread/src/device.c \
../rt-thread/src/idle.c \
../rt-thread/src/ipc.c \
../rt-thread/src/irq.c \
../rt-thread/src/kservice.c \
../rt-thread/src/mem.c \
../rt-thread/src/mempool.c \
../rt-thread/src/object.c \
../rt-thread/src/scheduler.c \
../rt-thread/src/signal.c \
../rt-thread/src/thread.c \
../rt-thread/src/timer.c 

OBJS += \
./rt-thread/src/clock.o \
./rt-thread/src/components.o \
./rt-thread/src/device.o \
./rt-thread/src/idle.o \
./rt-thread/src/ipc.o \
./rt-thread/src/irq.o \
./rt-thread/src/kservice.o \
./rt-thread/src/mem.o \
./rt-thread/src/mempool.o \
./rt-thread/src/object.o \
./rt-thread/src/scheduler.o \
./rt-thread/src/signal.o \
./rt-thread/src/thread.o \
./rt-thread/src/timer.o 

C_DEPS += \
./rt-thread/src/clock.d \
./rt-thread/src/components.d \
./rt-thread/src/device.d \
./rt-thread/src/idle.d \
./rt-thread/src/ipc.d \
./rt-thread/src/irq.d \
./rt-thread/src/kservice.d \
./rt-thread/src/mem.d \
./rt-thread/src/mempool.d \
./rt-thread/src/object.d \
./rt-thread/src/scheduler.d \
./rt-thread/src/signal.d \
./rt-thread/src/thread.d \
./rt-thread/src/timer.d 


# Each subdirectory must supply rules for building sources it contributes
rt-thread/src/%.o: ../rt-thread/src/%.c
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -ffunction-sections -fdata-sections -Wall  -g -gdwarf-2 -DDEBUG -I"E:\RTT_project\5.oled\iic\drivers" -I"E:\RTT_project\5.oled\iic\libraries" -I"E:\RTT_project\5.oled\iic\libraries\CMSIS\Device\ST\STM32F1xx\Include" -I"E:\RTT_project\5.oled\iic\libraries\CMSIS\Include" -I"E:\RTT_project\5.oled\iic\libraries\STM32F1xx_HAL_Driver\Inc" -I"E:\RTT_project\5.oled\iic" -I"E:\RTT_project\5.oled\iic\rt-thread\components\drivers\include" -I"E:\RTT_project\5.oled\iic\rt-thread\components\finsh" -I"E:\RTT_project\5.oled\iic\rt-thread\components\libc\compilers\minilibc" -I"E:\RTT_project\5.oled\iic\rt-thread\include" -I"E:\RTT_project\5.oled\iic\rt-thread\libcpu\arm\common" -I"E:\RTT_project\5.oled\iic\rt-thread\libcpu\arm\cortex-m3" -include"E:\RTT_project\5.oled\iic\rtconfig_preinc.h" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

