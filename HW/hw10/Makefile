C = gcc
CFLAGS  = -g
DEPS    = Makefile
OBJS    = hw10.o
EXECS   = hw10

all:    $(EXECS)

%.o:    %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

hw10: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	/bin/rm -i *.o $(EXECSi)
