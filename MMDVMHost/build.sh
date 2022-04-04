sudo service cron stop
rpi-rw
make -j4
mv MMDVMHost ../../W0CHP-PiStar-bin
mv RemoteCommand ../../W0CHP-PiStar-bin

make clean

make -j4 -f Makefile.Pi.Adafruit
mv MMDVMHost_Adafruit ../../W0CHP-PiStar-bin
make clean

sudo service cron start

