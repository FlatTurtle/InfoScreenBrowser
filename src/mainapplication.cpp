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
    setOrganizationDomain("flatturtle.com");
    setApplicationName("InfoScreenBrowser");
    setApplicationVersion("0.6");

    // Load the settings
    mSettings = new QSettings(this);

    // Start the subsystems
    try {
        mUserInterface = new UserInterface();
        mUserInterface->showFullScreen();

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
