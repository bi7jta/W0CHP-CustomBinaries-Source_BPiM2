sudo service cron stop
rpi-rw

make clean

make -j4
mv MMDVMHost ~/dev/W0CHP-PiStar-bin
mv RemoteCommand ~/dev/W0CHP-PiStar-bin

make clean

make -j4 -f Makefile.Pi.Adafruit
mv MMDVMHost_Adafruit ~/dev/W0CHP-PiStar-bin

make clean

sudo service cron start

