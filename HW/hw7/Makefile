CC = gcc
CFLAGS  = -g
DEPS    = Makefile
OBJS    = hw7.o
EXECS   = hw7

all:    $(EXECS)

%.o:    %.c $(DEPS)
	        $(CC) $(CFLAGS) -c -o $@ $<

hw7: $(OBJS)
	               $(CC) $(CFLAGS) -o $@ $^

clean:
	        /bin/rm -i *.o $(EXECS)
