//
// Configuration
//

// Include guard
#ifndef MAINAPPLICATION_H
#define MAINAPPLICATION_H

// Library includes
#include <QtCore/QObject>
#include <QtCore/QSettings>
#include <QtGui/QApplication>
#include <QtCore/QSocketNotifier>

// Local includes
#include "qexception.h"
#include "userinterface.h"

namespace iRail
{
    class MainApplication : public QApplication
    {
        Q_OBJECT
    public:
        // Construction and destruction
        explicit MainApplication(int& argc, char** argv) throw(QException);
        ~MainApplication();

        // System signals (Unix)
        static void handleInterruptUnix(int unused);
        static void handleTerminateUnix(int unused);

    public slots:
        // System signals
        void handleInterrupt();
        void handleTerminate();

        // Singleton object getters
    public:
        static MainApplication *instance();

        // Subsystem object getters
    public:
        UserInterface* userInterface() const;

        // Application control
    public:
        void start();
        void fatal();

        // UI events
    public slots:
        void run();
        void quitGracefully();

    private:
        // Singleton object
        static MainApplication *mInstance;

        // Subsystem objects
        QSettings* mSettings;
        UserInterface* mUserInterface;

        static int sigintFd[2];
        static int sigtermFd[2];

        QSocketNotifier *snInt;
        QSocketNotifier *snTerm;
    };
}



#endif // MAINAPPLICATION_H
