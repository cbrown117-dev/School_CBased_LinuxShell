C = gcc
CFLAGS  = -g
DEPS    = Makefile
OBJS    = hw9.o
EXECS   = hw9

all:    $(EXECS)

%.o:    %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

hw9: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	/bin/rm -i *.o $(EXECSi)
