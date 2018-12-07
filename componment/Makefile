objs := list.o init.o thread.o scheduler.o wait.o timer.o command.o

pres := list.i init.i thread.i scheduler.i wait.i timer.i command.i

all : $(objs)
	arm-none-eabi-ld -r -o componment.o $^

pre : $(pres)
	
%.o : %.c
	arm-none-eabi-gcc ${CFLAGS} $^
	
%.o : %.S
	arm-none-eabi-gcc ${CFLAGS} $^

%.i : %.c
	arm-none-eabi-gcc ${CFLAGS} -E $^ -o $@

clean:
	rm -f *.o *.i
	
