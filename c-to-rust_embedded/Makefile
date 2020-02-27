# ifeq ($(shell uname),Darwin)
#     LDFLAGS := -Wl,-dead_strip
# else
#     LDFLAGS := -Wl,--gc-sections -lpthread -ldl
# endif

PREFIX = arm-none-eabi-
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
else
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

CPU = -mcpu=cortex-m0plus
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

LDSCRIPT = STM32L072CZEx_FLASH.ld

# libraries
# LIBS = -lc  -lnosys
LIBS = -lnosys
LIBDIR =
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=target/double.map,--cref -Wl,--gc-sections

# compile gcc flags
OPT ?= -g -O0
CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

# ASM sources
ASM_SOURCES =  Projects/Multi/Applications/LoRa/AT_Slave/SW4STM32/B-L072Z-LRWAN1/startup_stm32l072xx.s

C_SOURCES = src/startup_stm32l072xx.c \
			src/stm32l0xx_it.c \
			src/main.c

RUST_STATICLIB = target/thumbv6m-none-eabi/debug/libdouble_input.a

OBJ_DIR = target

OBJECTS = $(addprefix $(OBJ_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
# vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(OBJ_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
# vpath %.s $(sort $(dir $(ASM_SOURCES)))

# rust staticlibs must come last in link order
OBJECTS += $(RUST_STATICLIB)

$(info OBJECTS = $(OBJECTS))

# OBJECTS = target/thumbv6m-none-eabi/debug/libdouble_input.a \
# 		  target/main.o

all: target/double
	$(SZ) target/double

target:
	mkdir -p $@

target/double: $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

$(RUST_STATICLIB): src/lib.rs Cargo.toml
	cargo build

target/%.o: src/%.c | target
	$(CC) $(CFLAGS) -o $@ -c $<

# Plain output, for S
target/%.o: src/%.s | target
	$(AS) -c $(ASLAGS) $< -o $@

clean:
	rm -rf target


