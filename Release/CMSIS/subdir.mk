################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CMSIS/system_MKL25Z4.c 

C_DEPS += \
./CMSIS/system_MKL25Z4.d 

OBJS += \
./CMSIS/system_MKL25Z4.o 


# Each subdirectory must supply rules for building sources it contributes
CMSIS/%.o: ../CMSIS/%.c CMSIS/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DPRINTF_FLOAT_ENABLE=0 -DSCANF_FLOAT_ENABLE=0 -DPRINTF_ADVANCED_ENABLE=0 -DSCANF_ADVANCED_ENABLE=0 -DFRDM_KL25Z -DFREEDOM -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DNDEBUG -D__REDLIB__ -I"D:\1st_Sem\PES\Assignments\Assignment_4\assignment-4-traptibalgiCUB\source" -I"D:\1st_Sem\PES\Assignments\Assignment_4\assignment-4-traptibalgiCUB" -I"D:\1st_Sem\PES\Assignments\Assignment_4\assignment-4-traptibalgiCUB\CMSIS" -I"D:\1st_Sem\PES\Assignments\Assignment_4\assignment-4-traptibalgiCUB\drivers" -I"D:\1st_Sem\PES\Assignments\Assignment_4\assignment-4-traptibalgiCUB\utilities" -I"D:\1st_Sem\PES\Assignments\Assignment_4\assignment-4-traptibalgiCUB\startup" -I"D:\1st_Sem\PES\Assignments\Assignment_4\assignment-4-traptibalgiCUB\board" -O0 -fno-common -g -Wall -Werror -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-CMSIS

clean-CMSIS:
	-$(RM) ./CMSIS/system_MKL25Z4.d ./CMSIS/system_MKL25Z4.o

.PHONY: clean-CMSIS

