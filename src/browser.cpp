//
// Configuration
//

// Local includes
#include "browser.h"

// Library includes
#include <QtCore/QDebug>
#include <QtNetwork/QHostInfo>


//
// Construction and destruction
//

FlatTurtle::Browser::Browser(QObject *iParent)
    : QObject(iParent) {
    mWebView = new QWebView();

    connect(mWebView, SIGNAL(loadStarted()), this, SLOT(onLoadStarted()));
    connect(mWebView, SIGNAL(loadProgress(int)), this, SLOT(onLoadProgress(int)));
    connect(mWebView, SIGNAL(loadFinished(bool)), this, SLOT(onLoadFinished(bool)));
}

FlatTurtle::WebPage::WebPage(QWidget *iParent)
    : QWebPage(iParent) {
}


//
// Infoscreen interface
//

// TODO: remove this and embed the QWebView in a QWidget (didn't seem to expand properly)
QWebView *FlatTurtle::Browser::view() {
    return mWebView;
}

void FlatTurtle::Browser::start() {
    mWebView->setPage((QWebPage*) new WebPage());

    QHostInfo tInfo;
    mWebView->load(QUrl("http://go.flatturtle.com/" + tInfo.localHostName()));
}


//
// UI slots
//

void FlatTurtle::Browser::onLoadStarted() {
    qDebug() << "Started loading";
}

void FlatTurtle::Browser::onLoadProgress(int progress) {
    qDebug() << "Load in progress:" << progress;
}

void FlatTurtle::Browser::onLoadFinished(bool ok) {
    if (ok)
        qDebug() << "Loading finished";
    else
        qWarning() << "Loading failed";
}


//
// WebPage interface
//

QString FlatTurtle::WebPage::userAgentForUrl(const QUrl &iUrl) const {
    return QString("FlatTurtle 1.0 - Qt");
}

void FlatTurtle::WebPage::javaScriptConsoleMessage(const QString& iMessage, int iLineNumber, const QString& iSourceId) {
    qDebug() << "Javascript console message at line " << iLineNumber << " of " << iSourceId << ": " << iMessage;
}
