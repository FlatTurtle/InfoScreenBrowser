//
// Configuration
//

// Local includes
#include "mainapplication.h"

// Library includes
#include <QtGui/QDesktopServices>
#include <QtCore/QDir>
#include <QtCore/QTimer>
#include <QtCore/QDebug>

// System includes
#include <csignal>
#include <sys/socket.h>

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

// Initialize static members
MainApplication* MainApplication::mInstance = NULL;
int MainApplication::sigintFd[2];
int MainApplication::sigtermFd[2];

MainApplication::MainApplication(int& argc, char** argv) throw(QException) : QApplication(argc, argv)
{
    qDebug() << Q_FUNC_INFO;

    // Singleton assertion (well, some singleton-hybrid, to be fair)
    Q_ASSERT(mInstance == NULL);
    mInstance = this;

    // Configure the application
    setOrganizationName("iRail");
    setOrganizationDomain("irail.be");
    setApplicationName("InfoScreen");
    setApplicationVersion("0.1");

    // Setup signal handling
    if (::socketpair(AF_UNIX, SOCK_STREAM, 0, sigintFd))
        qFatal("Couldn't create HUP socketpair");
    if (::socketpair(AF_UNIX, SOCK_STREAM, 0, sigtermFd))
        qFatal("Couldn't create TERM socketpair");
    snInt = new QSocketNotifier(sigintFd[1], QSocketNotifier::Read, this);
    connect(snInt, SIGNAL(activated(int)), this, SLOT(handleInterrupt()));
    snTerm = new QSocketNotifier(sigtermFd[1], QSocketNotifier::Read, this);
    connect(snTerm, SIGNAL(activated(int)), this, SLOT(handleTerminate()));

    // Load the settings
    mSettings = new QSettings(this);

    // Initialize subsystems
    qDebug() << "Loading subsystems";
    try
    {
        qDebug() << "Initializing user interface";
        mUserInterface = new UserInterface();
        mUserInterface->show();
    }
    catch (const QException& iException)
    {
        qDebug() << "Failed to initialize: " + iException.what();
        throw QException("could not load all subsystems");
    }
}

MainApplication::~MainApplication()
{
    qDebug() << Q_FUNC_INFO;

    // Remove the singleton configuration
    mInstance = NULL;
}


//
// Application control
//

void MainApplication::start()
{
    qDebug() << Q_FUNC_INFO;

    QTimer::singleShot(0, this, SLOT(run()));
    QObject::connect(this, SIGNAL(lastWindowClosed()), this, SLOT(quitGracefully()));
}

void MainApplication::fatal()
{
    qDebug() << Q_FUNC_INFO;

    qFatal("Fatal error occured, halting application");
    quitGracefully();
}

//
// Singleton objects getters
//

MainApplication *MainApplication::instance()
{
    qDebug() << Q_FUNC_INFO;

    return mInstance;
}


//
// Subsystem object getters
//

UserInterface* MainApplication::userInterface() const
{
    qDebug() << Q_FUNC_INFO;

    return mUserInterface;
}

//
// UI events
//

void MainApplication::run()
{
    qDebug() << Q_FUNC_INFO;
}

void MainApplication::quitGracefully()
{
    qDebug() << Q_FUNC_INFO;
    qDebug() << "Closing down";

    // Do some stuff here

    // Delete subsystems
    delete mUserInterface;

    // Actually quit
    quit();
}


//
// System signals (Unix)
//

void MainApplication::handleInterruptUnix(int)
{
    qDebug() << Q_FUNC_INFO;

    // Write to the SIGINT-socket
    char a = '1';
    ::write(sigintFd[0], &a, sizeof(a));

}

void MainApplication::handleTerminateUnix(int)
{
    qDebug() << Q_FUNC_INFO;

    // Write to the SIGTERM-socket
    char a = '2';
    ::write(sigtermFd[0], &a, sizeof(a));
}

//
// System signals
//

void MainApplication::handleTerminate()
{
    qDebug() << Q_FUNC_INFO;

    // Read the socket and temporarily disable the signal
    snTerm->setEnabled(false);
    char tmp;
    ::read(sigtermFd[1], &tmp, sizeof(tmp));

    // Quit the application
    quitGracefully();

    snTerm->setEnabled(true);
}

void MainApplication::handleInterrupt()
{
    qDebug() << Q_FUNC_INFO;

    // Read the socket and temporarily disable the signal
    snInt->setEnabled(false);
    char tmp;
    ::read(sigintFd[1], &tmp, sizeof(tmp));

    // Quit the application
    quitGracefully();

    snInt->setEnabled(true);
}
