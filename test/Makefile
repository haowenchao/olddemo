objs := cmd_nand.o

pres := cmd_nand.i

all : $(objs)
	arm-none-eabi-ld -r -o test.o $^

pre : $(pres)
	
%.o : %.c
	arm-none-eabi-gcc ${CFLAGS} $^
	
%.o : %.S
	arm-none-eabi-gcc ${CFLAGS} $^

%.i : %.c
	arm-none-eabi-gcc ${CFLAGS} -E $^ -o $@

clean:
	rm -f *.o *.i
	
