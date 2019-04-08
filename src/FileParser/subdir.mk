################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/FileParser/UTIL_FileParser.c 

OBJS += \
./src/FileParser/UTIL_FileParser.o 

C_DEPS += \
./src/FileParser/UTIL_FileParser.d 

# Each subdirectory must supply rules for building sources it contributes
src/FileParser/%.o: ../src/FileParser/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	@echo  current_dir
	gcc -I"\..\FileParser" -I"\..\KeyValueStore" -I"\..\ArgumentProcess" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


