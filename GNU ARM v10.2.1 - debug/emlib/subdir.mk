################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_cmu.c \
C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_core.c \
C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_emu.c \
C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_gpio.c \
C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_iadc.c \
C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_system.c 

OBJS += \
./emlib/em_cmu.o \
./emlib/em_core.o \
./emlib/em_emu.o \
./emlib/em_gpio.o \
./emlib/em_iadc.o \
./emlib/em_system.o 

C_DEPS += \
./emlib/em_cmu.d \
./emlib/em_core.d \
./emlib/em_emu.d \
./emlib/em_gpio.d \
./emlib/em_iadc.d \
./emlib/em_system.d 


# Each subdirectory must supply rules for building sources it contributes
emlib/em_cmu.o: C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_cmu.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DEFR32MG22C224F512IM40=1' -I"C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/EFR32MG22_BRD4182A/config" -I"C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Include" -I"C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/bsp" -I"C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/drivers" -I"C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFR32MG22/Include" -O0 -Wall -ffunction-sections -fdata-sections -mfpu=fpv5-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -mcmse -MMD -MP -MF"emlib/em_cmu.d" -MT"emlib/em_cmu.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_core.o: C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_core.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DEFR32MG22C224F512IM40=1' -I"C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/EFR32MG22_BRD4182A/config" -I"C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Include" -I"C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/bsp" -I"C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/drivers" -I"C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFR32MG22/Include" -O0 -Wall -ffunction-sections -fdata-sections -mfpu=fpv5-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -mcmse -MMD -MP -MF"emlib/em_core.d" -MT"emlib/em_core.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_emu.o: C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_emu.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DEFR32MG22C224F512IM40=1' -I"C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/EFR32MG22_BRD4182A/config" -I"C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Include" -I"C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/bsp" -I"C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/drivers" -I"C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFR32MG22/Include" -O0 -Wall -ffunction-sections -fdata-sections -mfpu=fpv5-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -mcmse -MMD -MP -MF"emlib/em_emu.d" -MT"emlib/em_emu.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_gpio.o: C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_gpio.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DEFR32MG22C224F512IM40=1' -I"C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/EFR32MG22_BRD4182A/config" -I"C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Include" -I"C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/bsp" -I"C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/drivers" -I"C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFR32MG22/Include" -O0 -Wall -ffunction-sections -fdata-sections -mfpu=fpv5-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -mcmse -MMD -MP -MF"emlib/em_gpio.d" -MT"emlib/em_gpio.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_iadc.o: C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_iadc.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DEFR32MG22C224F512IM40=1' -I"C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/EFR32MG22_BRD4182A/config" -I"C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Include" -I"C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/bsp" -I"C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/drivers" -I"C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFR32MG22/Include" -O0 -Wall -ffunction-sections -fdata-sections -mfpu=fpv5-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -mcmse -MMD -MP -MF"emlib/em_iadc.d" -MT"emlib/em_iadc.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_system.o: C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_system.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DEFR32MG22C224F512IM40=1' -I"C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/EFR32MG22_BRD4182A/config" -I"C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Include" -I"C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/bsp" -I"C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/drivers" -I"C:/Users/jruda/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFR32MG22/Include" -O0 -Wall -ffunction-sections -fdata-sections -mfpu=fpv5-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -mcmse -MMD -MP -MF"emlib/em_system.d" -MT"emlib/em_system.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


