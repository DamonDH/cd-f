################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/fingertipdetect.cpp \
../src/imgtrainer.cpp \
../src/main.cpp \
../src/speaker.cpp \
../src/vision.cpp 

OBJS += \
./src/fingertipdetect.o \
./src/imgtrainer.o \
./src/main.o \
./src/speaker.o \
./src/vision.o 

CPP_DEPS += \
./src/fingertipdetect.d \
./src/imgtrainer.d \
./src/main.d \
./src/speaker.d \
./src/vision.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include -I/usr/local/include/opencv -I/usr/local/include/opencv2 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


