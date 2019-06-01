objs := context.o  exception.o  interrupt.o  main.o  rtc.o  swi.o  timer.o

all : $(objs)
	arm-none-eabi-ld -r -o built-in.o $^

pre : $(pres)
	
%.o : %.c
	arm-none-eabi-gcc ${CFLAGS} $^
	
%.o : %.S
	arm-none-eabi-gcc ${CFLAGS} $^

%.i : %.c
	arm-none-eabi-gcc ${CFLAGS} -E $^ -o $@

clean:
	rm -f *.o *.i

