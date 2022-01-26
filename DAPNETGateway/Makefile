CC      = cc
CXX     = c++
CFLAGS  = -g -O3 -Wall -DHAVE_LOG_H -std=c++0x -pthread
LIBS    = -lm -lpthread
LDFLAGS = -g

OBJECTS = Conf.o DAPNETGateway.o DAPNETNetwork.o Log.o POCSAGMessage.o POCSAGNetwork.o StopWatch.o TCPSocket.o Thread.o Timer.o UDPSocket.o Utils.o REGEX.o

all:		DAPNETGateway

DAPNETGateway:	$(OBJECTS)
		$(CXX) $(OBJECTS) $(CFLAGS) $(LIBS) -o DAPNETGateway

%.o: %.cpp
		$(CXX) $(CFLAGS) -c -o $@ $<

DAPNETGateway.o: GitVersion.h FORCE

.PHONY: GitVersion.h

FORCE:

install:
		install -m 755 DAPNETGateway /usr/local/bin/

clean:
		$(RM) DAPNETGateway *.o *.d *.bak *~ GitVersion.h

GitVersion.h:
		echo "const char *gitversion = \"$(shell git rev-parse HEAD)\";" > $@


