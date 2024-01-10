################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../utilities/fsl_debug_console.c 

C_DEPS += \
./utilities/fsl_debug_console.d 

OBJS += \
./utilities/fsl_debug_console.o 


# Each subdirectory must supply rules for building sources it contributes
utilities/%.o: ../utilities/%.c utilities/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DDEBUG -DPRINTF_FLOAT_ENABLE=1 -DSCANF_FLOAT_ENABLE=0 -DPRINTF_ADVANCED_ENABLE=0 -DSCANF_ADVANCED_ENABLE=0 -DFRDM_KL25Z -DFREEDOM -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DSDK_DEBUGCONSOLE=0 -I"D:\1st_Sem\PES\Backup\PES_Backup\Final_Project\source" -I"D:\1st_Sem\PES\Backup\PES_Backup\Final_Project" -I"D:\1st_Sem\PES\Backup\PES_Backup\Final_Project\CMSIS" -I"D:\1st_Sem\PES\Backup\PES_Backup\Final_Project\drivers" -I"D:\1st_Sem\PES\Backup\PES_Backup\Final_Project\utilities" -I"D:\1st_Sem\PES\Backup\PES_Backup\Final_Project\startup" -I"D:\1st_Sem\PES\Backup\PES_Backup\Final_Project\board" -O0 -fno-common -g -Wall -Werror -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-utilities

clean-utilities:
	-$(RM) ./utilities/fsl_debug_console.d ./utilities/fsl_debug_console.o

.PHONY: clean-utilities

