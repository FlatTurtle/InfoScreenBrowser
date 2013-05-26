//
// Configuration
//

// Header includes
#include "browser.h"

// Library includes
#include <QTimer>
#include <QtCore/QDebug>
#include <QtNetwork/QHostInfo>
#include <QtWebKit/QWebFrame>
#include <QtCore/QProcess>
#include <QDir>
// Local includes
#include "mainapplication.h"


//
// Construction and destruction
//

FlatTurtle::Browser::Browser(QObject *iParent)
    : QObject(iParent) {
    QSettings settings(QString(QDir::homePath() + "/.infoscreenbrowser"), QSettings::IniFormat);
    bool pluginsEnabled = settings.value("browser/pluginsenabled", true).toBool();
    if(pluginsEnabled){
        QWebSettings::globalSettings()->setAttribute(QWebSettings::PluginsEnabled, true);
    }

    QWebSettings::setMaximumPagesInCache(1);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(clearCache()));
    timer->start(5000);

    mWebView = new QWebView();
    mWebView->setPage((QWebPage*) new WebPage());

#ifdef DEVEL
    qWarning() << "WARNING: using development infoscreen";
    mWebView->load(QUrl("https://go.flatturtle.com/"));
#else
    QHostInfo tInfo;
    mWebView->load(QUrl("https://go.flatturtle.com/" + tInfo.localHostName()));
#endif
    //connect the urlChanged signal to the urlChanged slot of this class
    connect(mWebView,SIGNAL(urlChanged(const QUrl)), this, SLOT(urlChanged (const QUrl)));
}

void FlatTurtle::Browser::clearCache(){
    QWebSettings::clearMemoryCaches();
    qApp->processEvents();
}

void FlatTurtle::Browser::urlChanged(const QUrl &url){
    // Make the application interface available to Javascript code each time the url changes
    mWebView->page()->mainFrame()->addToJavaScriptWindowObject("application", mWebView->page());
    ((WebPage*)mWebView->page())->setUserAgent("FlatTurtle InfoScreenBrowser/" + MainApplication::instance()->applicationVersion() + " QtWebKit/" + QTWEBKIT_VERSION_STR);
}

FlatTurtle::WebPage::WebPage(QWidget *iParent)
    : QWebPage(iParent) {
    // Make the application interface available to Javascript code
    mainFrame()->addToJavaScriptWindowObject("application", this);
    mUserAgent = "FlatTurtle InfoScreenBrowser/" + MainApplication::instance()->applicationVersion() + " QtWebKit/" + QTWEBKIT_VERSION_STR;
}

/* The Plugin stuff */
QObject *FlatTurtle::WebPage::createPlugin(
		const QString &classid,
		const QUrl &,
		const QStringList &,
		const QStringList &)
{
	QObject *result = 0;
	result = static_cast<QObject*>(
			QMetaType::construct(
				QMetaType::type(
					classid.toLatin1())));
	return result;
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

void FlatTurtle::WebPage::setUserAgent(const QString &str) {
    mUserAgent = str;
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
    tArguments << "/usr/local/bin/puppet-manual.sh";
    return sudo(tArguments, tOutput);
}

bool FlatTurtle::WebPage::enableScreen(bool iEnabled) {
    QString tOutput;
    QStringList tArguments;
    tArguments << "dpms" << "force" << (iEnabled ? "on" : "off");
    return system("/usr/bin/xset", tArguments, tOutput);
}

bool FlatTurtle::WebPage::soundControl(const QString &cmd) {
    QString tOutput;
    QSettings settings(QString(QDir::homePath() + "/.infoscreenbrowser"), QSettings::IniFormat);
    QString password = settings.value("mpd/password", "").toString();
    QStringList tArguments;
    if(password != ""){
        tArguments << "-h" << password;
    }
    tArguments += cmd.split(QRegExp(" "));
    return system("/usr/bin/mpc",tArguments, tOutput);
}

bool FlatTurtle::WebPage::takeScreenshot(const QString & mail = "" ) {
    QString tOutput;
    QStringList tArguments;
    tArguments << mail;
    return system("/usr/local/bin/screenshot.sh", tArguments, tOutput);
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
