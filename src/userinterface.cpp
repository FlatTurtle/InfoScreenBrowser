//
// Configuration
//

// Local includes
#include "userinterface.h"
#include "mainapplication.h"

// Library includes
#include <QtCore/QStringList>
#include <QtCore/QDebug>

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

UserInterface::UserInterface(QWidget *parent) throw(QException) : QMainWindow(parent)
{
    // Load settings
    mSettings = new QSettings(this);
    mSettings->beginGroup("UserInterface");

    // Setup UI
    mBrowser = new Browser(this);
    setCentralWidget(mBrowser->view());
    showMaximized();

    // Load web page
    qDebug() << "Showing page";
    mBrowser->start();
}
