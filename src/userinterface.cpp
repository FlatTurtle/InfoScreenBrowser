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
    connect(mBrowser, SIGNAL(loadStarted()), this, SLOT(onLoadStarted()));
    connect(mBrowser, SIGNAL(loadProgress(int)), this, SLOT(onLoadProgress(int)));
    connect(mBrowser, SIGNAL(loadFinished(bool)), this, SLOT(onLoadFinished(bool)));
    setCentralWidget(mBrowser);
    showMaximized();

    // Load web page
    qDebug() << "Showing page";
    mBrowser->start();
}


//
// UI slots
//


void UserInterface::onLoadStarted()
{
    qDebug() << "Started loading";
}

void UserInterface::onLoadProgress(int progress)
{
    qDebug() << "Load in progress:" << progress;
}

void UserInterface::onLoadFinished(bool ok)
{
    if (ok)
        qDebug() << "Loading finished";
    else
        qWarning() << "Loading failed";
}
