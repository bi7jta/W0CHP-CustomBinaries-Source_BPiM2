CC      = cc
CXX     = c++
CFLAGS  = -s -O3 -Wall -std=c++0x -pthread
LIBS    = -lpthread
LDFLAGS = -g

OBJECTS = NXDNNetwork.o NXDNParrot.o Parrot.o StopWatch.o Thread.o Timer.o UDPSocket.o

all:		NXDNParrot

NXDNParrot:	$(OBJECTS)
		$(CXX) $(OBJECTS) $(CFLAGS) $(LIBS) -o NXDNParrot

%.o: %.cpp
		$(CXX) $(CFLAGS) -c -o $@ $<

install:
		install -m 755 NXDNParrot $(HOME)/dev/W0CHP-PiStar-bin/

clean:
		$(RM) NXDNParrot *.o *.d *.bak *~
