C = gcc
CFLAGS  = -g -pthread
DEPS    = Makefile
OBJS    = hw13.o
EXECS   = hw13

all:    $(EXECS)

%.o:    %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

hw13: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	/bin/rm -i *.o $(EXECSi)
