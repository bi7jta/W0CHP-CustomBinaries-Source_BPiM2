export DATADIR := "/usr/local/etc"
export LOGDIR  := "/var/log/pi-star"
export CONFDIR := "/etc"
export BINDIR  := "$(HOME)/dev/W0CHP-PiStar-bin/"

export CXX     := $(shell wx-config --cxx)
export CFLAGS  := -s -O2 -Wall $(shell wx-config --cxxflags) -DLOG_DIR='$(LOGDIR)' -DCONF_DIR='$(CONFDIR)' -DDATA_DIR='$(DATADIR)' -DGPIO
export GUILIBS := $(shell wx-config --libs adv,core,base) -lasound
export LIBS    := $(shell wx-config --libs base) -lasound -lusb-1.0 -lwiringPi
export LDFLAGS :=

#all:	DStarRepeater/dstarrepeaterd DStarRepeaterConfig/dstarrepeaterconfig
all:	DStarRepeater/dstarrepeaterd

DStarRepeater/dstarrepeaterd:	Common/Common.a force
	$(MAKE) -C DStarRepeater

#DStarRepeaterConfig/dstarrepeaterconfig:	GUICommon/GUICommon.a Common/Common.a force
#	$(MAKE) -C DStarRepeaterConfig

#GUICommon/GUICommon.a: force
	#$(MAKE) -C GUICommon

Common/Common.a: force
	$(MAKE) -C Common

.PHONY: install
install:	all
	#$(MAKE) -C Data install
	$(MAKE) -C DStarRepeater install
	#$(MAKE) -C DStarRepeaterConfig install

.PHONY: clean
clean:
	$(MAKE) -C Common clean
	$(MAKE) -C GUICommon clean
	$(MAKE) -C DStarRepeater clean
	$(MAKE) -C DStarRepeaterConfig clean

.PHONY: force
force:
	@true
