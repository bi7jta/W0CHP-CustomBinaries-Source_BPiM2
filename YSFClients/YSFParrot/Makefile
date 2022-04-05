CC      = cc
CXX     = c++
CFLAGS  = -s -O3 -Wall -std=c++0x -pthread
LIBS    = -lpthread
LDFLAGS = -g

OBJECTS = Network.o Parrot.o StopWatch.o Thread.o Timer.o UDPSocket.o YSFParrot.o

all:		YSFParrot

YSFParrot:	$(OBJECTS)
		$(CXX) $(OBJECTS) $(CFLAGS) $(LIBS) -o YSFParrot

%.o: %.cpp
		$(CXX) $(CFLAGS) -c -o $@ $<

YSFParrot.o: GitVersion.h FORCE

.PHONY: GitVersion.h

FORCE:

install:
		install -m 755 YSFParrot $(HOME)/dev/W0CHP-PiStar-bin/

clean:
		$(RM) YSFParrot *.o *.d *.bak *~ GitVersion.h
 
GitVersion.h:
		echo "const char *gitversion = \"$(shell git rev-parse HEAD)\";" > $@
