################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/PWM.c \
../source/main.c \
../source/mtb.c \
../source/semihost_hardfault.c \
../source/switch.c \
../source/timers.c \
../source/touch_slider.c \
../source/train_fsm.c \
../source/train_states.c 

C_DEPS += \
./source/PWM.d \
./source/main.d \
./source/mtb.d \
./source/semihost_hardfault.d \
./source/switch.d \
./source/timers.d \
./source/touch_slider.d \
./source/train_fsm.d \
./source/train_states.d 

OBJS += \
./source/PWM.o \
./source/main.o \
./source/mtb.o \
./source/semihost_hardfault.o \
./source/switch.o \
./source/timers.o \
./source/touch_slider.o \
./source/train_fsm.o \
./source/train_states.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DPRINTF_FLOAT_ENABLE=0 -DSCANF_FLOAT_ENABLE=0 -DPRINTF_ADVANCED_ENABLE=0 -DSCANF_ADVANCED_ENABLE=0 -DFRDM_KL25Z -DFREEDOM -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DNDEBUG -D__REDLIB__ -I"D:\1st_Sem\PES\Assignments\Assignment_4\assignment-4-traptibalgiCUB\source" -I"D:\1st_Sem\PES\Assignments\Assignment_4\assignment-4-traptibalgiCUB" -I"D:\1st_Sem\PES\Assignments\Assignment_4\assignment-4-traptibalgiCUB\CMSIS" -I"D:\1st_Sem\PES\Assignments\Assignment_4\assignment-4-traptibalgiCUB\drivers" -I"D:\1st_Sem\PES\Assignments\Assignment_4\assignment-4-traptibalgiCUB\utilities" -I"D:\1st_Sem\PES\Assignments\Assignment_4\assignment-4-traptibalgiCUB\startup" -I"D:\1st_Sem\PES\Assignments\Assignment_4\assignment-4-traptibalgiCUB\board" -O0 -fno-common -g -Wall -Werror -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/PWM.d ./source/PWM.o ./source/main.d ./source/main.o ./source/mtb.d ./source/mtb.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o ./source/switch.d ./source/switch.o ./source/timers.d ./source/timers.o ./source/touch_slider.d ./source/touch_slider.o ./source/train_fsm.d ./source/train_fsm.o ./source/train_states.d ./source/train_states.o

.PHONY: clean-source

