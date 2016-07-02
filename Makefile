
CC=cc

# Possible platforms are SUN, HPUX, DEC, SGI, AIX, Linux and MSDOS
# The main definitions are for 32/16 bits and for byte order, the 
# default is big endian.  You can do -D__TNEF_BYTE_ORDER 1234 for little
# endian
PLATFORM=-D___TNEF_BYTE_ORDER=4321 
#CFLAGS = -O2 -ggdb
CFLAGS = -O2  -Wall
OBJS=logger.o tnef.o

all: $(OBJS) opentnef

.c.o:
	${CC} ${CFLAGS} $(PLATFORM) -c $*.c


default: opentnef

opentnef: opentnef.c $(OBJS)
	$(CC) $(CFLAGS) $(PLATFORM) $(OBJS) opentnef.c -o opentnef

install: opentnef
	cp opentnef /usr/local/bin
	
clean:
	rm -f *.o *.~[ch]
