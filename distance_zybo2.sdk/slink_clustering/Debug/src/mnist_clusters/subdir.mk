################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/mnist_clusters/mnist_clusters_0.c \
../src/mnist_clusters/mnist_clusters_1.c \
../src/mnist_clusters/mnist_clusters_2.c \
../src/mnist_clusters/mnist_clusters_3.c \
../src/mnist_clusters/mnist_clusters_4.c \
../src/mnist_clusters/mnist_clusters_5.c \
../src/mnist_clusters/mnist_clusters_6.c \
../src/mnist_clusters/mnist_clusters_7.c \
../src/mnist_clusters/mnist_clusters_8.c \
../src/mnist_clusters/mnist_clusters_9.c 

OBJS += \
./src/mnist_clusters/mnist_clusters_0.o \
./src/mnist_clusters/mnist_clusters_1.o \
./src/mnist_clusters/mnist_clusters_2.o \
./src/mnist_clusters/mnist_clusters_3.o \
./src/mnist_clusters/mnist_clusters_4.o \
./src/mnist_clusters/mnist_clusters_5.o \
./src/mnist_clusters/mnist_clusters_6.o \
./src/mnist_clusters/mnist_clusters_7.o \
./src/mnist_clusters/mnist_clusters_8.o \
./src/mnist_clusters/mnist_clusters_9.o 

C_DEPS += \
./src/mnist_clusters/mnist_clusters_0.d \
./src/mnist_clusters/mnist_clusters_1.d \
./src/mnist_clusters/mnist_clusters_2.d \
./src/mnist_clusters/mnist_clusters_3.d \
./src/mnist_clusters/mnist_clusters_4.d \
./src/mnist_clusters/mnist_clusters_5.d \
./src/mnist_clusters/mnist_clusters_6.d \
./src/mnist_clusters/mnist_clusters_7.d \
./src/mnist_clusters/mnist_clusters_8.d \
./src/mnist_clusters/mnist_clusters_9.d 


# Each subdirectory must supply rules for building sources it contributes
src/mnist_clusters/%.o: ../src/mnist_clusters/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 gcc compiler'
	arm-none-eabi-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -I../../standalone_bsp_0/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


