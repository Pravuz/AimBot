################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/cr_cpp_config.cpp \
../src/cr_startup_lpc43xx.cpp \
../src/exec.cpp \
../src/flash.cpp \
../src/main_m4.cpp \
../src/proggreyshades.cpp 

C_SRCS += \
../src/cr_start_m0.c \
../src/system_LPC43xx.c 

OBJS += \
./src/cr_cpp_config.o \
./src/cr_start_m0.o \
./src/cr_startup_lpc43xx.o \
./src/exec.o \
./src/flash.o \
./src/main_m4.o \
./src/proggreyshades.o \
./src/system_LPC43xx.o 

C_DEPS += \
./src/cr_start_m0.d \
./src/system_LPC43xx.d 

CPP_DEPS += \
./src/cr_cpp_config.d \
./src/cr_startup_lpc43xx.d \
./src/exec.d \
./src/flash.d \
./src/main_m4.d \
./src/proggreyshades.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -D__MULTICORE_MASTER -DIPC_MASTER -DPIXY -D__NEWLIB__ -DNDEBUG -D__CODE_RED -DCORE_M4 -DCPP_USE_HEAP -D__LPC43XX__ -DLPC43_MULTICORE_M0APP -D__MULTICORE_MASTER_SLAVE_M0APP -I"C:\Users\ouroborus\Dropbox\Bacheloroppgave 2015\Utvikling og Kode\Pixy_3_3_15\gcc\video\inc" -I"C:\Users\ouroborus\Dropbox\Bacheloroppgave 2015\Utvikling og Kode\Pixy_3_3_15\gcc\pixy_m4\inc" -O1 -Os -g3 -w -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -fsingle-precision-constant -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -D__NEWLIB__ -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/cr_start_m0.o: ../src/cr_start_m0.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DIPC_MASTER -DPIXY -D__MULTICORE_MASTER -DNDEBUG -D__CODE_RED -DCORE_M4 -DCPP_USE_HEAP -D__LPC43XX__ -DLPC43_MULTICORE_M0APP -D__MULTICORE_MASTER_SLAVE_M0APP -D__NEWLIB__ -I"C:\Users\ouroborus\Dropbox\Bacheloroppgave 2015\Utvikling og Kode\Pixy_3_3_15\gcc\video\inc" -I"C:\Users\ouroborus\Dropbox\Bacheloroppgave 2015\Utvikling og Kode\Pixy_3_3_15\gcc\pixy_m4\inc" -Os -g3 -w -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fsingle-precision-constant -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -D__NEWLIB__ -MMD -MP -MF"$(@:%.o=%.d)" -MT"src/cr_start_m0.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DIPC_MASTER -DPIXY -D__MULTICORE_MASTER -DNDEBUG -D__CODE_RED -DCORE_M4 -DCPP_USE_HEAP -D__LPC43XX__ -DLPC43_MULTICORE_M0APP -D__MULTICORE_MASTER_SLAVE_M0APP -D__NEWLIB__ -I"C:\Users\ouroborus\Dropbox\Bacheloroppgave 2015\Utvikling og Kode\Pixy_3_3_15\gcc\video\inc" -I"C:\Users\ouroborus\Dropbox\Bacheloroppgave 2015\Utvikling og Kode\Pixy_3_3_15\gcc\pixy_m4\inc" -Os -g3 -w -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fsingle-precision-constant -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -D__NEWLIB__ -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


