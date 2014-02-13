#!/bin/bash
rm ../infoscreenbrowser*
git pull
rm debian/rules
ln -s `pwd`/debian/i386-rules debian/rules
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
echo ""
echo ""
echo "----------------------------------"
echo "all done... sign & publicize with:"
echo "----------------------------------"
echo "(1)	dpkg-sig -k repository@flatturtle.com --sign builder infoscreenbrowser_..."
echo "(2)	reprepro --verbose --basedir /srv/debian/i386 includedeb wheezy infoscreenbrowser_..."
echo ""
