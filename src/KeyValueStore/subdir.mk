################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/KeyValueStore/UTIL_KVS.c 

OBJS += \
./src/KeyValueStore/UTIL_KVS.o 

C_DEPS += \
./src/KeyValueStore/UTIL_KVS.d 


# Each subdirectory must supply rules for building sources it contributes
src/KeyValueStore/%.o: ../src/KeyValueStore/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"\..\FileParser" -I"\..KeyValueStore" -I"\..ArgumentProcess" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


