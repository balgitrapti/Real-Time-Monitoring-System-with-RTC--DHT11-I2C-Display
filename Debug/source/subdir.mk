################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/DHT11.c \
../source/I2C.c \
../source/LCD.c \
../source/RTC.c \
../source/UART.c \
../source/UART_terminal.c \
../source/cbfifo.c \
../source/main.c \
../source/mtb.c \
../source/processor.c \
../source/semihost_hardfault.c \
../source/timers.c 

C_DEPS += \
./source/DHT11.d \
./source/I2C.d \
./source/LCD.d \
./source/RTC.d \
./source/UART.d \
./source/UART_terminal.d \
./source/cbfifo.d \
./source/main.d \
./source/mtb.d \
./source/processor.d \
./source/semihost_hardfault.d \
./source/timers.d 

OBJS += \
./source/DHT11.o \
./source/I2C.o \
./source/LCD.o \
./source/RTC.o \
./source/UART.o \
./source/UART_terminal.o \
./source/cbfifo.o \
./source/main.o \
./source/mtb.o \
./source/processor.o \
./source/semihost_hardfault.o \
./source/timers.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DDEBUG -DPRINTF_FLOAT_ENABLE=1 -DSCANF_FLOAT_ENABLE=0 -DPRINTF_ADVANCED_ENABLE=0 -DSCANF_ADVANCED_ENABLE=0 -DFRDM_KL25Z -DFREEDOM -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DSDK_DEBUGCONSOLE=0 -I"D:\1st_Sem\PES\Backup\PES_Backup\Final_Project\source" -I"D:\1st_Sem\PES\Backup\PES_Backup\Final_Project" -I"D:\1st_Sem\PES\Backup\PES_Backup\Final_Project\CMSIS" -I"D:\1st_Sem\PES\Backup\PES_Backup\Final_Project\drivers" -I"D:\1st_Sem\PES\Backup\PES_Backup\Final_Project\utilities" -I"D:\1st_Sem\PES\Backup\PES_Backup\Final_Project\startup" -I"D:\1st_Sem\PES\Backup\PES_Backup\Final_Project\board" -O0 -fno-common -g -Wall -Werror -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/DHT11.d ./source/DHT11.o ./source/I2C.d ./source/I2C.o ./source/LCD.d ./source/LCD.o ./source/RTC.d ./source/RTC.o ./source/UART.d ./source/UART.o ./source/UART_terminal.d ./source/UART_terminal.o ./source/cbfifo.d ./source/cbfifo.o ./source/main.d ./source/main.o ./source/mtb.d ./source/mtb.o ./source/processor.d ./source/processor.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o ./source/timers.d ./source/timers.o

.PHONY: clean-source

