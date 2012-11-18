QT += core gui network webkit xml phonon

TARGET = infoscreenbrowser

CONFIG += link_pkgconfig

PKGCONFIG += QJson qxmpp

#DEFINES += DEVEL

SOURCES += \
    main.cpp \
    mainapplication.cpp \
    userinterface.cpp \
    browser.cpp \
    networkinterface.cpp \
    myplayer.cpp

HEADERS += \
    mainapplication.h \
    userinterface.h \
    qexception.h \
    browser.h \
    networkinterface.h \
    myplayer.h

unix {
    isEmpty(PREFIX) {
      PREFIX = /usr
    }
    BINDIR = $$PREFIX/bin
    DATADIR =$$PREFIX/share
    INSTALLS += target
    target.path = $$BINDIR
}

OTHER_FILES += \
    config.example.ini
