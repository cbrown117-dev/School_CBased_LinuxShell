C = gcc
CFLAGS  = -g -pthread
DEPS    = Makefile
OBJS    = hw12.o
EXECS   = hw12

all:    $(EXECS)

%.o:    %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

hw12: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	/bin/rm -i *.o $(EXECSi)
