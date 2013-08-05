#!/bin/bash
rm debian/rules
ln -s `pwd`/debian/efikamx-rules debian/rules
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
echo "-----------------"
echo "all done... sign & publicize with:"
echo "dpkg-sig -k repository@flatturtle.com --sign builder infoscreenbrowser..."
echo "reprepro --verbose --basedir /srv/debian includedeb wheezy infoscreenbrowser..."
