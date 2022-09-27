#!/usr/bin/env bash

SRC_DIR=$HOME/dev/WPSD_CustomBinaries-Source
DEST_DIR=$HOME/dev/W0CHP-PiStar-bin

cd $SRC_DIR/APRSGateway ; make clean ; make -j5 ; make install ; make clean
cd $SRC_DIR/MMDVMHost ; make clean ; make -j5 ; make install ; make clean ; \
     make -j5 -f Makefile.Pi.Adafruit ; make -f Makefile.Pi.Adafruit install ; make -f Makefile.Pi.Adafruit clean
cd $SRC_DIR/DAPNETGateway ; make clean ; make -j5 ; make install ; make clean
cd $SRC_DIR/DMRGateway ; make clean ; make -j5 ; make install ; make clean
cd $SRC_DIR/DStarRepeater ; make clean ; make -j5 ; make install ; make clean
cd $SRC_DIR/ircDDBGateway ; make clean ; make -j5 ; make install ; make clean
cd $SRC_DIR/M17Gateway ; make clean ; make -j5 ; make install ; make clean
cd $SRC_DIR/MMDVMCal ; make clean ; make -j5 ; make install ; make clean
cd $SRC_DIR/MMDVM_CM/DMR2YSF ; make clean ; make -j5 ; make install ; make clean
cd $SRC_DIR/MMDVM_CM/DMR2NXDN ; make clean ; make -j5 ; make install ; make clean
cd $SRC_DIR/MMDVM_CM/YSF2DMR ; make clean ; make -j5 ; make install ; make clean
cd $SRC_DIR/MMDVM_CM/YSF2P25 ; make clean ; make -j5 ; make install ; make clean
cd $SRC_DIR/MMDVM_CM/YSF2NXDN ; make clean ; make -j5 ; make install ; make clean
cd $SRC_DIR/MMDVM_CM/NXDN2DMR ; make clean ; make -j5 ; make install ; make clean
cd $SRC_DIR/NXDNClients ; make clean ; make -j5 ; make install ; make clean
cd $SRC_DIR/P25Clients ; make clean ; make -j5 ; make install ; make clean
cd $SRC_DIR/YSFClients ; make clean ; make -j5 ; make install ; make clean
cd $SRC_DIR/NextionDriver ; make clean ; make -j5 ; make install ; make clean

strip `find $DEST_DIR -type f -executable -exec file -i '{}' \; | grep 'x-executable; charset=binary' | sed 's/:.*//g'`
