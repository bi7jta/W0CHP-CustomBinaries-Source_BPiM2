
CC     ?= gcc
CXX    ?= g++
CFLAGS += -Wall -O2 -D_GNU_SOURCE

SOURCE = \
		NextionDriver.c basicFunctions.c processCommands.c processButtons.c helpers.c

all:		clean NextionDriver

NextionDriver:
		$(CC) $(SOURCE) $(CFLAGS) -o NextionDriver

.PHONY install:
install: all
		install -m 755 NextionDriver $(HOME)/dev/W0CHP-PiStar-bin/

clean:
		$(RM) NextionDriver *.o *.d *.bak *~
