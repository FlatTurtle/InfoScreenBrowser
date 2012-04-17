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

bool FlatTurtle::WebPage::shouldInterruptJavaScript() {
    return false;
}


//
// Application interface
//

bool FlatTurtle::WebPage::reboot() {
    QString tOutput;
    QStringList tArguments;
    tArguments << "/sbin/reboot";
    return sudo(tArguments, tOutput);
}

bool FlatTurtle::WebPage::puppetUpdate() {
    QString tOutput;
    QStringList tArguments;
    tArguments << "/usr/sbin/puppetd" << "--onetime" << "--logdest" << "syslog";
    return sudo(tArguments, tOutput);
}

bool FlatTurtle::WebPage::enableScreen(bool iEnabled) {
    QString tOutput;
    QStringList tArguments;
    tArguments << "dpms" << "force" << (iEnabled ? "on" : "off");
    return system("/usr/bin/xset", tArguments, tOutput);
}


//
// Auxiliary
//

bool FlatTurtle::WebPage::system(const QString& iCommand, const QStringList& iArguments, QString& oOutput) {
    // Set-up the process
    qDebug() << "DEBUG: executing system command" << iCommand << "with arguments" << iArguments.join(" ");
    QProcess tProcess(this);
    tProcess.setProcessChannelMode(QProcess::MergedChannels);
    tProcess.start(iCommand, iArguments);

    // Wait for the end of the command
    QEventLoop tLoop;
    connect(&tProcess, SIGNAL(finished(int, QProcess::ExitStatus)), &tLoop, SLOT(quit()));
    tLoop.exec();

    // Return appropriate data
    oOutput = tProcess.readAll();
    return (tProcess.exitStatus() == QProcess::NormalExit);
}

bool FlatTurtle::WebPage::sudo(const QStringList& iArguments, QString& oOutput) {
    return system("/usr/bin/sudo", iArguments, oOutput);
}
