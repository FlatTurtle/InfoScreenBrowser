#!/bin/bash
ln -s debian/efikamx-rules debian/rules
rm src/Makefile
rm src/*.o
rm -r build/
mkdir build/
cd build/
/usr/local/Trolltech/Qt-4.8.4/bin/qmake ../
make
make install
cd ..
dch
dpkg-buildpackage -uc -us
rm debian/rules
