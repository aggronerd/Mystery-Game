################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../isometric.o 

CPP_SRCS += \
../Entity.cpp \
../Game.cpp \
../IsometricConversions.cpp \
../IsometricGrid.cpp \
../Level.cpp \
../Overlay.cpp \
../RandomGenerator.cpp \
../isometric.cpp 

OBJS += \
./Entity.o \
./Game.o \
./IsometricConversions.o \
./IsometricGrid.o \
./Level.o \
./Overlay.o \
./RandomGenerator.o \
./isometric.o 

CPP_DEPS += \
./Entity.d \
./Game.d \
./IsometricConversions.d \
./IsometricGrid.d \
./Level.d \
./Overlay.d \
./RandomGenerator.d \
./isometric.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include -I/usr/local/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


