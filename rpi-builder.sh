#!/bin/bash
ln -s debian/rpi-rules debian/rules
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
rm debian/rules
