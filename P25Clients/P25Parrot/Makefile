CC      = cc
CXX     = c++
CFLAGS  = -s -O3 -Wall -std=c++0x -pthread
LIBS    = -lpthread
LDFLAGS = -g

OBJECTS = Network.o P25Parrot.o Parrot.o StopWatch.o Thread.o Timer.o UDPSocket.o

all:		P25Parrot

P25Parrot:	$(OBJECTS)
		$(CXX) $(OBJECTS) $(CFLAGS) $(LIBS) -o P25Parrot

%.o: %.cpp
		$(CXX) $(CFLAGS) -c -o $@ $<

install:
		install -m 755 P25Parrot $(HOME)/dev/W0CHP-PiStar-bin/

clean:
		$(RM) P25Parrot *.o *.d *.bak *~
