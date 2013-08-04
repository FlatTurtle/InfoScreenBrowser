#!/bin/bash
rm debian/rules
ln -s `pwd`/debian/rpi-rules debian/rules
rm src/Makefile
rm src/*.o
rm -r build/
mkdir build/
cd build/
/usr/bin/qmake ../
make
make install
cd ..
dch
dpkg-buildpackage -uc -us
cd ..
rename s/"infoscreenbrowser"/"infoscreenbrowser_rpi_"/ infoscreenbrowser_*_armhf.deb

