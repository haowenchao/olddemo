CC		:= arm-none-eabi-gcc
LD		:= arm-none-eabi-ld
OBJDUMP		:= arm-none-eabi-objdump
OBJCOPY		:= arm-none-eabi-objcopy
READELF		:= arm-none-eabi-readelf
CFLAGS		:= -c -nostdinc -fno-builtin -I$(shell pwd)/include 
LDFLAGS		:= -Tlink.lds -nostdlib
OBJCOPYFLAGS	:= -O binary -S
OBJDUMPFLAGS	:= -D -S
export CC LD CFLAGS

objs := start.o board.o s3c24xx.o main.o nand.o swi.o interrupt.o exception.o rtc.o lib/lib.o

all:$(objs)
	$(LD) $(LDFLAGS) -o jz2440.elf $^
	$(OBJCOPY) $(OBJCOPYFLAGS) jz2440.elf jz2440.bin
	$(OBJDUMP) $(OBJDUMPFLAGS) jz2440.elf > jz2440.dis

%.o:%.c
	$(CC) $(CFLAGS) -o $@ $^

%.o:%.S
	$(CC) $(CFLAGS) -o $@ $^

lib/lib.o:
	make -C lib

PHONY:tags
tags:
	ctags -R
	cscope -Rbkq
clean:
	rm -rf *.o *.bin *.elf *.dis
	make -C lib clean

install:
	sudo oflash 0 1 0 0 0 jz2440.bin
distclean:
	rm -rf *.o *.bin *.elf *.dis cscope* tags
	make -C lib clean

