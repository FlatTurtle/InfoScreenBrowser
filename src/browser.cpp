//
// Configuration
//

// Header includes
#include "browser.h"

// Library includes
#include <QtCore/QDebug>
#include <QtNetwork/QHostInfo>
#include <QtWebKit/QWebFrame>
#include <QtCore/QProcess>

// Local includes
#include "mainapplication.h"


//
// Construction and destruction
//

FlatTurtle::Browser::Browser(QObject *iParent)
    : QObject(iParent) {
    mWebView = new QWebView();
    mWebView->setPage((QWebPage*) new WebPage());

#ifdef DEVEL
    qWarning() << "WARNING: using development infoscreen";
    mWebView->load(QUrl("http://go.flatturtle.com/development"));
#else
    QHostInfo tInfo;
    mWebView->load(QUrl("http://go.flatturtle.com/" + tInfo.localHostName()));
#endif
}

FlatTurtle::WebPage::WebPage(QWidget *iParent)
    : QWebPage(iParent) {
    // Make the application interface available to Javascript code
    mainFrame()->addToJavaScriptWindowObject("application", this);

    mUserAgent = "InfoScreenBrowser/" + MainApplication::instance()->applicationVersion() + " QtWebKit/" + QTWEBKIT_VERSION_STR;
}


//
// Infoscreen interface
//

// TODO: remove this and embed the QWebView in a QWidget (didn't seem to expand properly)
QWebView *FlatTurtle::Browser::view() {
    return mWebView;
}

QVariant FlatTurtle::Browser::execute(const QString& iCode) {
    return mWebView->page()->mainFrame()->evaluateJavaScript(iCode);
}


//
// WebPage interface
//

QString FlatTurtle::WebPage::userAgentForUrl(const QUrl &iUrl) const {
    return mUserAgent;
}

void FlatTurtle::WebPage::javaScriptConsoleMessage(const QString& iMessage, int iLineNumber, const QString& iSourceId) {
    qDebug() << "Javascript console message at line " << iLineNumber << " of " << iSourceId << ": " << iMessage;
}


//
// Application interface
//

QString FlatTurtle::WebPage::system(const QString& iCommand) {
    // TODO: return the return code, but how to send the stdout/stderr back?
    qDebug() << "DEBUG: executing system command" << iCommand;
    QProcess tScript(this);
    tScript.setProcessChannelMode(QProcess::MergedChannels);
    tScript.start(iCommand);
    if (tScript.waitForFinished())
        return tScript.readAll();
    else
        return tScript.errorString();
}
