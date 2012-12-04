#!/bin/bash
rm -r build
mkdir build && cd build
#qmake ../
/usr/local/Trolltech/Qt-4.8.3/bin/qmake ../
make
make install
cd ..
dch
dpkg-buildpackage -uc -us
