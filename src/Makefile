BIN=stm32_firmware.bin
ELF=stm32_firmware.elf

LIBOPENCM3=../libopencm3/lib/libopencm3_stm32f1.a

SRC=                        \
main.c                      \
usart.c

LKR_SCRIPT = linker/stm32f103x8.ld

ARM_TOOLCHAIN_PATH=../toolchain/bin
ARM_TOOLCHAIN_PRFIX=arm-none-eabi-

CROSS_COMPILE=$(ARM_TOOLCHAIN_PATH)/$(ARM_TOOLCHAIN_PRFIX)

CC=$(CROSS_COMPILE)gcc
AR=$(CROSS_COMPILE)ar
CP=$(CROSS_COMPILE)objcopy
LD=$(CROSS_COMPILE)ld
LDCONFIG=$(CROSS_COMPILE)ldconfig
STRIP=$(CROSS_COMPILE)strip

INCLUDE=-I.                                                     \
        -I./../libopencm3/include/libopencmsis/stm32/f1/        \
        -I./../libopencm3/include/

CFLAGS=-c -fno-common -O0 -g -mcpu=cortex-m3 -mthumb -DSTM32F1
LDFLAGS=-nostartfiles -specs=nano.specs -mcpu=cortex-m3 -mthumb -T$(LKR_SCRIPT) $(LIBOPENCM3) 
CPFLAGS=-Obinary
ASFLAGS=-c -mcpu=cortex-m3 -mthumb 

OBJECTS=$(SRC:.c=.o)

all:$(BIN)
	@echo "[ build $(BIN) ]"

%.o:%.c
	@ echo "[ Compile .c -> .o ]"
	@$(CC) $(INCLUDE) $(CFLAGS) $< -o $@

$(ELF):$(OBJECTS)
	@ echo "[ Create ELF ]"
	@$(CC) -o $(ELF) $(OBJECTS) $(LDFLAGS)

$(BIN): $(LIBOPENCM3) $(ELF)
	@ echo "[ objcopy elf to bin ]"
	@ $(CP) $(CPFLAGS) $(ELF) $(BIN)

libopencm3:
	@echo "[ Build Libopencm3 for stm32f1 ]"
	@cd ../libopencm3/ && export PATH=$$PATH:$(shell pwd)/../toolchain/bin/ && $(MAKE) lib/stm32/f1

$(LIBOPENCM3):libopencm3

.PHONY:clean

dist_clean:clean clean_libopencm3
	@echo "[ Clean ALL project ]"

clean:
	@echo "[ clean SRC ]"
	@rm -f $(OBJECTS)
	@rm -f $(BIN)
	@rm -f $(ELF)

clean_libopencm3:
	@echo "[ Clean Libopencm3 ]"
	@cd ../libopencm3/ && export PATH=$$PATH:$(shell pwd)/../toolchain/bin/ && $(MAKE) clean

write:$(ELF)
	openocd -f ../config/openocd.cfg -c "init" \
									 -c "reset halt" \
									 -c "flash probe 0" \
									 -c "flash protect 0 0 63 off" \
									 -c "reset halt" \
									 -c "stm32f1x mass_erase 0" \
									 -c "flash write_image stm32_firmware.elf" \
									 -c "reset run" \
									 -c "exit"













