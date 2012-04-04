/**
  *Copyright (C) 2011-2012 Tim Besard <tim.besard@gmail.com>
 *
  *All rights reserved.
 */

//
// Configuration
//

// Include guard
#ifndef MAINAPPLICATION_H_
#define MAINAPPLICATION_H_

// Library includes
#include <QtCore/QObject>
#include <QtCore/QSettings>
#include <QtGui/QApplication>
#include <QtCore/QSocketNotifier>
#include <QtCore/QDateTime>

// Local includes
#include "qexception.h"
#include "userinterface.h"
#include "networkinterface.h"

namespace FlatTurtle {
    class MainApplication : public QApplication {
    Q_OBJECT
    public:
        // Construction and destruction
        explicit MainApplication(int &iArgumentCount, char **iArgumentValues) throw(QException);
        ~MainApplication();

        // Subsystem getters
        UserInterface *userInterface() const;
        NetworkInterface *networkInterface() const;

        // Singleton object getters
    public:
        static MainApplication *instance();

    private:
        // Singleton object
        static MainApplication *mInstance;

        // Subsystem objects
        QSettings *mSettings;
        UserInterface *mUserInterface;
        NetworkInterface *mNetworkInterface;
    };
}

#endif  // MAINAPPLICATION_H_
