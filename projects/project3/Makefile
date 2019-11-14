C = gcc
CFLAGS  = -g
DEPS    = Makefile
OBJS    = project3.o
EXECS   = project3

all:    $(EXECS)

%.o:    %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

project3: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	/bin/rm -i *.o $(EXECSi)
