objs := list.o init.o

all : $(objs)
	arm-none-eabi-ld -r -o componment.o $^
	
%.o : %.c
	arm-none-eabi-gcc ${CFLAGS} $^
	
%.o : %.S
	arm-none-eabi-gcc ${CFLAGS} $^

clean:
	rm -f *.o		
	
