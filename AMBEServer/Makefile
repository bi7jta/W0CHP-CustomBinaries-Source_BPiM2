all:	AMBEserver

GCC := gcc

CFLAGS := -s -O2 -DRASPBERRY_PI -Wall -std=gnu99
CFLAGS2 := -O2 -Wall -std=gnu99

AMBEserver:	GitVersion.h AMBEserver.o
	$(GCC) $(CFLAGS) -o AMBEserver AMBEserver.o 
	
AMBEserver.o:	AMBEserver.c
	$(GCC) $(CFLAGS2) -c AMBEserver.c

clean:
	$(RM) -f AMBEserver *~ *.bak *.o GitVersion.h

install:
	install -m 755 AMBEserver $(HOME)/dev/W0CHP-PiStar-bin/

init-install:
	install init.d/AMBEserver /etc/init.d

GitVersion.h:
	echo "const char *gitversion = \"$(shell git rev-parse HEAD)\";" > $@
