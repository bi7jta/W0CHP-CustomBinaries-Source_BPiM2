CC      = cc
CXX     = c++

# Use the following CFLAGS and LIBS if you don't want to use gpsd.
CFLAGS  = -s -O3 -Wall -DHAVE_LOG_H -std=c++0x -pthread
LIBS    = -lm -lpthread

# Use the following CFLAGS and LIBS if you do want to use gpsd.
#CFLAGS  = -s -O3 -Wall -DHAVE_LOG_H -DUSE_GPSD -std=c++0x -pthread
#LIBS    = -lm -lpthread -lgps

LDFLAGS = -g

OBJECTS = APRSWriter.o Conf.o CRC.o DTMF.o FCSNetwork.o Golay24128.o GPS.o Log.o StopWatch.o Sync.o Thread.o Timer.o \
	  UDPSocket.o Utils.o WiresX.o YSFConvolution.o YSFFICH.o YSFGateway.o YSFNetwork.o YSFPayload.o YSFReflectors.o

all:		YSFGateway

YSFGateway:	$(OBJECTS)
		$(CXX) $(OBJECTS) $(CFLAGS) $(LIBS) -o YSFGateway

%.o: %.cpp
		$(CXX) $(CFLAGS) -c -o $@ $<

YSFGateway.o: GitVersion.h FORCE

.PHONY: GitVersion.h

FORCE:

install:
		install -m 755 YSFGateway $(HOME)/dev/W0CHP-PiStar-bin/

clean:
		$(RM) YSFGateway *.o *.d *.bak *~ GitVersion.h
 
GitVersion.h:
		echo "const char *gitversion = \"$(shell git rev-parse HEAD)\";" > $@
