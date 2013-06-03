/**
 * Copyright (C) 2011-2012 Tim Besard <tim.besard@gmail.com>
 * Copyright 2012-2013 FlatTurtle
 *
 * All rights reserved.
 */

//
// Configuration
//

// System includes
#include <csignal>
// Local includes
#include "mainapplication.h"
#include "myplayer.h"

struct ExitHandler {
    ExitHandler() {
        signal(SIGINT, &ExitHandler::exit);
        signal(SIGTERM, &ExitHandler::exit);
    }

    static void exit(int iExitCode) {
        // Calling exit in the QApplication will cause the aboutToQuit
        // signal to be emitted, allowing us to clean up properly from
        // within a Qt event thread (since this isn't, hence we cannot
        // call Qt functions from here).
        FlatTurtle::MainApplication::exit(iExitCode);
    }
};

int main(int iArgumentCount, char *iArgumentValues[]) {
    // Video player object meta type
	qRegisterMetaType<MyPlayer>("MyPlayer");

	// Handle Unix signals
    ExitHandler tExitHandler;

    // Run the applications
    FlatTurtle::MainApplication *tApplication = new FlatTurtle::MainApplication(iArgumentCount, iArgumentValues);
    return tApplication->exec();
}
