C = gcc
CFLAGS  = -g
DEPS    = Makefile
OBJS    = hw11.o
EXECS   = hw11

all:    $(EXECS)

%.o:    %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

hw11: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	/bin/rm -i *.o $(EXECSi)
