//
// Configuration
//

// Local includes
#include "browser.h"

// Library includes
#include <QtCore/QDebug>
#include <QtNetwork/QHostInfo>
#include <QtWebKit/QWebFrame>


//
// Construction and destruction
//

FlatTurtle::Browser::Browser(QObject *iParent)
    : QObject(iParent) {
    mWebView = new QWebView();
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

#ifdef DEVEL
    qWarning() << "Using development browser endpoint";
    mWebView->load(QUrl("http://go.flatturtle.com/development"));
#else
    QHostInfo tInfo;
    mWebView->load(QUrl("http://go.flatturtle.com/" + tInfo.localHostName()));
#endif
}

void FlatTurtle::Browser::execute(const QString& iCode) {
    mWebView->page()->mainFrame()->evaluateJavaScript(iCode);
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
