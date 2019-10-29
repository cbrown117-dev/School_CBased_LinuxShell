CC = gcc
CFLAGS  = -g
DEPS    = Makefile
OBJS    = project1.o
EXECS   = project1

all:    $(EXECS)

%.o:    %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

project1: $(OBJS)
	       $(CC) $(CFLAGS) -o $@ $^

clean:
	/bin/rm -i *.o $(EXECS)
