CC		=	gcc
CFLAGS	=

%.o: %.c
	gcc -c -o $@ $<

OBJS	= 	vm.o \
			tsort.o \
			test.o

default: test

obj: $(OBJS)

test: obj
	gcc -o test $(OBJS)

clean:
	rm -f *.o
	rm -f test
