//
// Configuration
//

// System includes
#include <signal.h>
#include <unistd.h>

// Local includes
#include "mainapplication.h"
#include "qexception.h"

// Library includes
#include <QtCore/QTextStream>

// Namespaces
using namespace iRail;

static int initSignalHandlers()
{
    // Set-up and register the SIGINT handler
    struct sigaction sigint;
    sigint.sa_handler = MainApplication::handleInterruptUnix;
    sigemptyset(&sigint.sa_mask);
    sigint.sa_flags = 0;
    sigint.sa_flags |= SA_RESTART;
    if (sigaction(SIGINT, &sigint, 0) > 0)
        return 1;

    // Set-up and register the SIGTERM handler
    struct sigaction sigterm;
    sigterm.sa_handler = MainApplication::handleTerminateUnix;
    sigemptyset(&sigterm.sa_mask);
    sigterm.sa_flags |= SA_RESTART;
    if (sigaction(SIGTERM, &sigterm, 0) > 0)
        return 2;

    return 0;
}

int main(int argc, char *argv[])
{
    // Handle Unix signals
    initSignalHandlers();

    // Initialize the application
    MainApplication* tApplication;
    try
    {
        tApplication = new MainApplication(argc, argv);
    }
    catch (const QException& iException)
    {
        QTextStream qerr(stderr);

        qerr << "--------------------------------------\n";
        qerr << "        INITIALIZATION FAILURE        \n";
        qerr << "--------------------------------------\n";
        qerr << "\n";
        qerr << "Exception details: " << iException.what() << "\n";

        return 0;
    }

    // Run the application
    try
    {
        tApplication->start();
        return tApplication->exec();
    }
    catch (const QException& iException)
    {
         QTextStream qerr(stderr);

         qerr << "---------------------------------------\n";
         qerr << "          UNTRAPPED EXCEPTION          \n";
         qerr << "---------------------------------------\n";
         qerr << "\n";
         qerr << "Exception details: " << iException.what() << "\n";

         return 0;
    }
}
