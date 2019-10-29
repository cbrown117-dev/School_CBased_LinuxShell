C = gcc
CFLAGS  = -g
DEPS    = Makefile
OBJS    = project2.o
EXECS   = project2

all:    $(EXECS)

%.o:    %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

project1: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	/bin/rm -i *.o $(EXECSi)
