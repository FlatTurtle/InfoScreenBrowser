//
// Configuration
//

// Local includes
#include "userinterface.h"
#include "mainapplication.h"

// Library includes
#include <QtCore/QStringList>
#include <QtCore/QDebug>


//
// Construction and destruction
//

FlatTurtle::UserInterface::UserInterface(QWidget *iParent) throw(QException)
    : QMainWindow(iParent) {
    // Load settings
    mSettings = new QSettings(this);
    mSettings->beginGroup(metaObject()->className());

    // Setup UI
    mBrowser = new Browser(this);
    setCentralWidget(mBrowser->view());
    showMaximized();

    // Load web page
    mBrowser->start();
}


//
// Functionality
//

void FlatTurtle::UserInterface::execute(const QString& iCode) {
    mBrowser->execute(iCode);
}
