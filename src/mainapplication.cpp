/**
  *Copyright (C) 2011-2012 Tim Besard <tim.besard@gmail.com>
 *
  *All rights reserved.
 */

//
// Configuration
//

// Header include
#include "mainapplication.h"

// System includes
#include <sys/socket.h>
#include <csignal>

// Library includes
#include <QtCore/QMetaType>
#include <QtCore/QDebug>
#include <QtGui/QDesktopServices>
#include <QtCore/QDir>
#include <QtCore/QStringBuilder>
#include <QtCore/QTimer>


//
// Construction and destruction
//

// Initialize static members
FlatTurtle::MainApplication *FlatTurtle::MainApplication::mInstance = NULL;

FlatTurtle::MainApplication::MainApplication(int &iArgumentCount, char **iArgumentValues) throw(QException)
    : QApplication(iArgumentCount, iArgumentValues) {
    // Singleton assertion (well, some singleton-hybrid, to be fair)
    Q_ASSERT(mInstance == NULL);
    mInstance = this;

    // Configure the application
    setOrganizationName("FlatTurtle");
    setOrganizationDomain("FlatTurtle.com");
    setApplicationName("InfoScreenBrowser");
    setApplicationVersion("1.0");

    // Load the settings
    mSettings = new QSettings(this);

    // Start the subsystems
    try {
        mUserInterface = new UserInterface();
        QSettings settings(QString(QDir::homePath() + "/.infoscreenbrowser"), QSettings::IniFormat);
        bool fullscreen = settings.value("browser/fullscreen", false).toBool();
        if(fullscreen){
            mUserInterface->showFullScreen();
        }

        mNetworkInterface = new NetworkInterface(this);
    }
    catch (const QException& iException) {
        qDebug() << "Failed to initialize: " + iException.what();
        throw QException("could not load all subsystems");
    }
}

FlatTurtle::MainApplication::~MainApplication() {
    // Remove the singleton configuration
    mInstance = NULL;
}


//
// Subsystem getters
//

FlatTurtle::UserInterface *FlatTurtle::MainApplication::userInterface() const {
    return mUserInterface;
}

FlatTurtle::NetworkInterface *FlatTurtle::MainApplication::networkInterface() const {
    return mNetworkInterface;
}


//
// Singleton objects getters
//

FlatTurtle::MainApplication *FlatTurtle::MainApplication::instance() {
    return mInstance;
}
