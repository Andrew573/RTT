################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libraries/CMSIS/Device/ST/STM32F1xx/Source/Templates/system_stm32f1xx.c 

OBJS += \
./libraries/CMSIS/Device/ST/STM32F1xx/Source/Templates/system_stm32f1xx.o 

C_DEPS += \
./libraries/CMSIS/Device/ST/STM32F1xx/Source/Templates/system_stm32f1xx.d 


# Each subdirectory must supply rules for building sources it contributes
libraries/CMSIS/Device/ST/STM32F1xx/Source/Templates/%.o: ../libraries/CMSIS/Device/ST/STM32F1xx/Source/Templates/%.c
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -ffunction-sections -fdata-sections -Wall  -g -gdwarf-2 -DDEBUG -I"E:\RTT_project\5.oled\iic\drivers" -I"E:\RTT_project\5.oled\iic\libraries" -I"E:\RTT_project\5.oled\iic\libraries\CMSIS\Device\ST\STM32F1xx\Include" -I"E:\RTT_project\5.oled\iic\libraries\CMSIS\Include" -I"E:\RTT_project\5.oled\iic\libraries\STM32F1xx_HAL_Driver\Inc" -I"E:\RTT_project\5.oled\iic" -I"E:\RTT_project\5.oled\iic\rt-thread\components\drivers\include" -I"E:\RTT_project\5.oled\iic\rt-thread\components\finsh" -I"E:\RTT_project\5.oled\iic\rt-thread\components\libc\compilers\minilibc" -I"E:\RTT_project\5.oled\iic\rt-thread\include" -I"E:\RTT_project\5.oled\iic\rt-thread\libcpu\arm\common" -I"E:\RTT_project\5.oled\iic\rt-thread\libcpu\arm\cortex-m3" -include"E:\RTT_project\5.oled\iic\rtconfig_preinc.h" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

