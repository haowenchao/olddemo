objs := div64.o lib1funcs.o ctype.o muldi3.o printf.o string.o vsprintf.o

all : $(objs)
	arm-none-eabi-ld -r -o lib.o $^
	
%.o : %.c
	arm-none-eabi-gcc ${CFLAGS} $^
	
%.o : %.S
	arm-none-eabi-gcc ${CFLAGS} $^

clean:
	rm -f *.o		
	
