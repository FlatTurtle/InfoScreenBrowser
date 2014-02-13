#-------------------------------------------------
#
# Project created by QtCreator 2013-12-17T15:44:52
#
#-------------------------------------------------

QT       += core gui network webkit xml phonon

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = infoscreenbrowser
TEMPLATE = app

CONFIG += link_pkgconfig
PKGCONFIG += QJson qxmpp

SOURCES += main.cpp\
        browser.cpp\
        myplayer.cpp\
        networkinterface.cpp\
        networktest.cpp\
        webpage.cpp

HEADERS  += browser.h\
            qexception.h\
            myplayer.h\
            networkinterface.h\
            networktest.h\
            webpage.h

FORMS    += browser.ui

#DEFINES += DEVEL

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
