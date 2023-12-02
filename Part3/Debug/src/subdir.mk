################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Test.cpp \
../src/TreeNode.cpp \
../src/makeDirectoryTree.cpp 

CPP_DEPS += \
./src/Test.d \
./src/TreeNode.d \
./src/makeDirectoryTree.d 

OBJS += \
./src/Test.o \
./src/TreeNode.o \
./src/makeDirectoryTree.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++2a -DUSE_OSS -I"/usr/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/Test.d ./src/Test.o ./src/TreeNode.d ./src/TreeNode.o ./src/makeDirectoryTree.d ./src/makeDirectoryTree.o

.PHONY: clean-src

