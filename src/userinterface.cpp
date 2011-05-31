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
    mWebView = new QWebView(this);
    setCentralWidget(mWebView);
    showMaximized();

    // Load debug page
    qDebug() << "Showing page";
    mWebView->setPage(new QWebPage());
    mWebView->load(QUrl("http://www.google.com/"));
}
