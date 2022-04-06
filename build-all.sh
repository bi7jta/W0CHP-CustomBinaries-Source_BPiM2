#!/usr/bin/env bash

ROOT_DIR=$HOME/dev/WPSD_CustomBinaries-Source

cd $ROOT_DIR/APRSGateway ; make clean ; make -j4 ; make install ; make clean
cd $ROOT_DIR/MMDVMHost ; make clean ; make -j4 ; make install ; make clean make -j4 -f Makefile.Pi.Adafruit ; make install ; make clean
cd $ROOT_DIR/DAPNETGateway ; make clean ; make -j4 ; make install ; make clean
cd $ROOT_DIR/DMRGateway ; make clean ; make -j4 ; make install ; make clean
cd $ROOT_DIR/DStarRepeater ; make clean ; make -j4 ; make install ; make clean
cd $ROOT_DIR/ircDDBGateway ; make clean ; make -j4 ; make install ; make clean
cd $ROOT_DIR/M17Gateway ; make clean ; make -j4 ; make install ; make clean
cd $ROOT_DIR/MMDVMCal ; make clean ; make -j4 ; make install ; make clean
cd $ROOT_DIR/MMDVM_CM/DMR2YSF ; make clean ; make -j4 ; make install ; make clean
cd $ROOT_DIR/MMDVM_CM/DMR2NXDN ; make clean ; make -j4 ; make install ; make clean
cd $ROOT_DIR/MMDVM_CM/YSF2DMR ; make clean ; make -j4 ; make install ; make clean
cd $ROOT_DIR/MMDVM_CM/YSF2P25 ; make clean ; make -j4 ; make install ; make clean
cd $ROOT_DIR/MMDVM_CM/YSF2NXDN ; make clean ; make -j4 ; make install ; make clean
cd $ROOT_DIR/MMDVM_CM/NXDN2DMR ; make clean ; make -j4 ; make install ; make clean
cd $ROOT_DIR/NXDNClients ; make clean ; make -j4 ; make install ; make clean
cd $ROOT_DIR/P25Clients ; make clean ; make -j4 ; make install ; make clean
cd $ROOT_DIR/YSFClients ; make clean ; make -j4 ; make install ; make clean

strip -v `find -type f -executable -exec file -i '{}' \; | grep 'x-executable; charset=binary' | sed 's/:.*//g'`
