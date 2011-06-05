//
// Configuration
//

// Local includes
#include "browser.h"

// Library includes
#include <QtCore/QDebug>

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

Browser::Browser(QObject* parent) : QObject(parent)
{
    mWebView = new QWebView();

    connect(mWebView, SIGNAL(loadStarted()), this, SLOT(onLoadStarted()));
    connect(mWebView, SIGNAL(loadProgress(int)), this, SLOT(onLoadProgress(int)));
    connect(mWebView, SIGNAL(loadFinished(bool)), this, SLOT(onLoadFinished(bool)));
}

WebPage::WebPage(QWidget *parent) : QWebPage(parent)
{

}


//
// Infoscreen interface
//

QWebView* Browser::view()
{
    return mWebView;
}

void Browser::start()
{
    mWebView->setPage((QWebPage*) new WebPage());
    mWebView->load(QUrl("http://www.google.be/"));
}


//
// UI slots
//

void Browser::onLoadStarted()
{
    qDebug() << "Started loading";
}

void Browser::onLoadProgress(int progress)
{
    qDebug() << "Load in progress:" << progress;
}

void Browser::onLoadFinished(bool ok)
{
    if (ok)
        qDebug() << "Loading finished";
    else
        qWarning() << "Loading failed";
}


//
// WebPage interface
//

QString WebPage::userAgentForUrl(const QUrl &iUrl) const
{
        return QString("irail-infoscreen");
}
