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
    qDebug() << Q_FUNC_INFO;

    mWebView = new QWebView();

    connect(mWebView, SIGNAL(loadStarted()), this, SLOT(onLoadStarted()));
    connect(mWebView, SIGNAL(loadProgress(int)), this, SLOT(onLoadProgress(int)));
    connect(mWebView, SIGNAL(loadFinished(bool)), this, SLOT(onLoadFinished(bool)));
}

WebPage::WebPage(QWidget *parent) : QWebPage(parent)
{
    qDebug() << Q_FUNC_INFO;
}


//
// Infoscreen interface
//

// TODO: remove this and embed the QWebView in a QWidget (didn't seem to expand properly)
QWebView* Browser::view()
{

    qDebug() << Q_FUNC_INFO;
    return mWebView;
}

void Browser::start()
{
    qDebug() << Q_FUNC_INFO;

    mWebView->setPage((QWebPage*) new WebPage());
    mWebView->load(QUrl("http://s.flatturtle.com/"));
}


//
// UI slots
//

void Browser::onLoadStarted()
{
    qDebug() << Q_FUNC_INFO;
    qDebug() << "Started loading";
}

void Browser::onLoadProgress(int progress)
{
    qDebug() << Q_FUNC_INFO;
    qDebug() << "Load in progress:" << progress;
}

void Browser::onLoadFinished(bool ok)
{
    qDebug() << Q_FUNC_INFO;
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
    qDebug() << Q_FUNC_INFO;
    return QString("irail-infoscreen");
}

void WebPage::javaScriptConsoleMessage(const QString& iMessage, int iLineNumber, const QString& iSourceId)
{
    qDebug() << Q_FUNC_INFO;
    qDebug() << "Javascript console message at line " << iLineNumber << " of " << iSourceId << ": " << iMessage;
}
