#!/bin/bash
rm -r build
mkdir build && cd build
qmake ../
make
make install
cd ..
dch
dpkg-buildpackage -uc -us
