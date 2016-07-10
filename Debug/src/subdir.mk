################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/BGModel.cpp \
../src/BGModelMog.cpp \
../src/ChromacityShadRem.cpp \
../src/ChromacityShadRemParams.cpp \
../src/GeometryShadRem.cpp \
../src/GeometryShadRemParams.cpp \
../src/LBMixtureOfGaussians.cpp \
../src/LBMixtureofGaussian.cpp \
../src/LrTextureShadRem.cpp \
../src/LrTextureShadRemParams.cpp \
../src/PhysicalShadRem.cpp \
../src/PhysicalShadRemParams.cpp \
../src/SrTextureShadRem.cpp \
../src/SrTextureShadRemParams.cpp \
../src/removeShadows.cpp 

OBJS += \
./src/BGModel.o \
./src/BGModelMog.o \
./src/ChromacityShadRem.o \
./src/ChromacityShadRemParams.o \
./src/GeometryShadRem.o \
./src/GeometryShadRemParams.o \
./src/LBMixtureOfGaussians.o \
./src/LBMixtureofGaussian.o \
./src/LrTextureShadRem.o \
./src/LrTextureShadRemParams.o \
./src/PhysicalShadRem.o \
./src/PhysicalShadRemParams.o \
./src/SrTextureShadRem.o \
./src/SrTextureShadRemParams.o \
./src/removeShadows.o 

CPP_DEPS += \
./src/BGModel.d \
./src/BGModelMog.d \
./src/ChromacityShadRem.d \
./src/ChromacityShadRemParams.d \
./src/GeometryShadRem.d \
./src/GeometryShadRemParams.d \
./src/LBMixtureOfGaussians.d \
./src/LBMixtureofGaussian.d \
./src/LrTextureShadRem.d \
./src/LrTextureShadRemParams.d \
./src/PhysicalShadRem.d \
./src/PhysicalShadRemParams.d \
./src/SrTextureShadRem.d \
./src/SrTextureShadRemParams.d \
./src/removeShadows.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include -I/usr/local/include/opencv -I/usr/local/include/opencv2 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


