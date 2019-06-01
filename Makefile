ifndef target
  target = a.out
endif

CROSS_COMPILE := arm-none-eabi-
CC      := $(CROSS_COMPILE)gcc
LD      := $(CROSS_COMPILE)ld
CPP     := $(CROSS_COMPILE)gcc
AR      := $(CROSS_COMPILE)ar
OBJDUMP := $(CROSS_COMPILE)objdump
OBJCOPY := $(CROSS_COMPILE)objcopy
export CC LD CPP AR OBJDUMP OBJCOPY

CFLAGS := -c -nostdinc -fno-builtin -I$(shell pwd)/include \
          -I$(shell pwd)/lib -I$(shell pwd)/board -Wall -O2 \
          -I$(shell pwd)/init -I$(shell pwd)
LDFLAGS		:= -T$(shell pwd)/script/link.lds -nostdlib
OBJCOPYFLAGS	:= -O binary -S
OBJDUMPFLAGS	:= -D -S
export CFLAGS LDFLAGS

ifeq ("$(origin V)", "command line")
  BUILD_VERBOSE = $(V)
endif

ifndef BUILD_VERBOSE
  BUILD_VERBOSE = 0
endif

ifeq ($(BUILD_VERBOSE),1)
  quiet =
  Q =
else
  quiet=quiet_
  Q = @
endif
export BUILD_VERBOSE quiet Q

MAKEFLAGS += --no-print-directory
TOPDIR := $(shell pwd)
SCRIPT := $(TOPDIR)/script
build  := -f $(SCRIPT)/Makefile.build -C
MAKE   := make
export TOPDIR SCRIPT build MAKE

PHONY    =
subdir   := init/ board/ componment/ test/
subdir-y := $(foreach v, $(filter %/, $(subdir)), $(patsubst %/, %/built-in.o, $v))
subdir   := $(foreach v, $(filter %/, $(subdir)), $(patsubst %/, %, $(v)))

all : $(subdir-y) lib/lib.o
	$(LD) $(LDFLAGS) -o jz2440.elf $^
	$(OBJCOPY) $(OBJCOPYFLAGS) jz2440.elf jz2440.bin
	$(OBJDUMP) $(OBJDUMPFLAGS) jz2440.elf > jz2440.dis

$(subdir-y) : $(subdir)

PHONY += $(subdir)
$(subdir) :
	$(Q) $(MAKE) $(build) $@

PHONY += lib/lib.o
lib/lib.o:
	make -C lib

PHONY += clean
clean:
	rm -rf jz2440.*
	find . -name "*.o"  | xargs rm -f
	find . -name "*.a"  | xargs rm -f

.PHONY : $(PHONY)

