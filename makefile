################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include src/subdir.mk
-include src/KeyValueStore/subdir.mk
-include src/FileParser/subdir.mk
-include src/ArgumentProcess/subdir.mk
-include src/.o/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: CommandLineCfg
	

# Tool invocations
CommandLineCfg: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C Linker'
	gcc  -o"CommandLineCfg" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) 
	

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) CommandLineCfg
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
