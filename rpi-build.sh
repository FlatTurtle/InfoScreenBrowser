#!/bin/bash
rm ../infoscreenbrowser*
git pull
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
rename s/"infoscreenbrowser"/"infoscreenbrowser_rpi"/ infoscreenbrowser_*_armhf.deb
echo ""
echo ""
echo "----------------------------------"
echo "all done... sign & publicize with:"
echo "----------------------------------"
echo "(1)	dpkg-sig -k repository@flatturtle.com --sign builder infoscreenbrowser_rpi..."
echo "(2)	reprepro --verbose --basedir /srv/debian/rpi includedeb wheezy infoscreenbrowser_rpi..."
echo "----------------------------------"
