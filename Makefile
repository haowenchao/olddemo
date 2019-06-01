CC		:= arm-none-eabi-gcc
LD		:= arm-none-eabi-ld
OBJDUMP		:= arm-none-eabi-objdump
OBJCOPY		:= arm-none-eabi-objcopy
READELF		:= arm-none-eabi-readelf
CFLAGS		:= -c -nostdinc -fno-builtin -I$(shell pwd)/include \
		-I$(shell pwd)/lib -I$(shell pwd) -Wall -O2
CFLAGS += -I$(shell pwd)/init
CFLAGS += -I$(shell pwd)/board

LDFLAGS		:= -Tscript/link.lds -nostdlib
OBJCOPYFLAGS	:= -O binary -S
OBJDUMPFLAGS	:= -D -S
export CC LD CFLAGS
HOSTCXXFLAGS := -O2 $(HOST_LFS_CFLAGS)

objs := init/built-in.o board/built-in.o lib/lib.o componment/componment.o test/test.o

pres := board.i s3c24xx.i main.i nand.i swi.i interrupt.i exception.i rtc.i

all:$(objs)
	$(LD) $(LDFLAGS) -o jz2440.elf $^
	$(OBJCOPY) $(OBJCOPYFLAGS) jz2440.elf jz2440.bin
	$(OBJDUMP) $(OBJDUMPFLAGS) jz2440.elf > jz2440.dis
	rm -rf componment/*.o

pre:$(pres)
	make -C componment pre

init/built-in.o :
	make -C init

board/built-in.o :
	make -C board

%.o:%.c
	$(CC) $(CFLAGS) -o $@ $^

%.o:%.S
	$(CC) $(CFLAGS) -o $@ $^

%.i:%.c
	$(CC) $(CFLAGS) -E -o $@ $^

lib/lib.o:
	make -C lib

test/test.o:
	make -C test

componment/componment.o:
	make -C componment

PHONY:tags
tags:
	ctags -R
	cscope -Rbkq
clean:
	rm -rf *.o *.bin *.elf *.dis *.i
	make -C lib clean
	make -C init clean
	make -C test clean
	make -C componment clean

install:
	sudo oflash 0 1 0 0 0 jz2440.bin

distclean:
	rm -rf *.o *.bin *.elf *.dis cscope* tags *.i
	make -C init clean
	make -C lib clean
	make -C test clean
	make -C componment clean

