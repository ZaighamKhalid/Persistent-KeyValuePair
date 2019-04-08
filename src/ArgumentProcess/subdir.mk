################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/ArgumentProcess/UTIL_ArgumentPocess.c 

OBJS += \
./src/ArgumentProcess/UTIL_ArgumentPocess.o 

C_DEPS += \
./src/ArgumentProcess/UTIL_ArgumentPocess.d 



# Each subdirectory must supply rules for building sources it contributes
src/ArgumentProcess/%.o: ../src/ArgumentProcess/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	@echo current_dir
	gcc -I"\..\FileParser" -I"\..\KeyValueStore" -I"\..ArgumentProcess" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


