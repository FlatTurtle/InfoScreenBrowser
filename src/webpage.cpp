// Library includes
#include <QTimer>
#include <QtCore/QDebug>
#include <QtNetwork/QHostInfo>
#include <QtWebKit/QWebFrame>
#include <QtCore/QProcess>
#include <QDir>
#include <QSettings>
#include <QApplication>

// Local includes
#include "browser.h"
#include "webpage.h"
#include "networktest.h"

WebPage::WebPage(QWidget *parent)
    : QWebPage(parent) {

    b = (Browser *)parent;

    connect(mainFrame(), SIGNAL(javaScriptWindowObjectCleared()),
               this, SLOT(populateJavaScriptWindowObject()) );

    useragent = "FlatTurtle InfoScreenBrowser/" +  QCoreApplication::applicationVersion() + " QtWebKit/" + QTWEBKIT_VERSION_STR;
}

void WebPage::populateJavaScriptWindowObject(){
    // Make the application interface available to Javascript code
    mainFrame()->addToJavaScriptWindowObject("application", this);
}

/* The Plugin stuff */
QObject *WebPage::createPlugin(
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
// WebPage interface
//

QString WebPage::userAgentForUrl(const QUrl &) const {
    return useragent;
}

void WebPage::setUserAgent(const QString &str) {
    useragent = str;
}
void WebPage::javaScriptConsoleMessage(const QString& message, int lineNumber, const QString& sourceId) {
    qDebug() << "Javascript console message at line " << lineNumber << " of " << sourceId << ": " << message;
}

bool WebPage::shouldInterruptJavaScript() {
    return false;
}

//
// Application interface
//

bool WebPage::reboot() {
    QString output;
    QStringList arguments;
    arguments << "/sbin/reboot";
    return sudo(arguments, output);
}

bool WebPage::puppetUpdate() {
    QString output;
    QStringList arguments;
    arguments << "/usr/local/bin/puppet-manual.sh";
    return sudo(arguments, output);
}

bool WebPage::enableScreen(bool enabled) {
    QString output;
    QStringList arguments;
    arguments << (enabled ? "on" : "off");
    return system("/usr/local/bin/powerdisplay.sh", arguments, output);
}

bool WebPage::soundControl(const QString &cmd) {
    QString output;
    QSettings settings(QString(QDir::homePath() + "/.infoscreenbrowser"), QSettings::IniFormat);
    QString password = settings.value("mpd/password", "").toString();
    QStringList arguments;
    if(password != ""){
        arguments << "-h" << password;
    }
    arguments += cmd.split(QRegExp(" "));
    return system("/usr/bin/mpc",arguments, output);
}

bool WebPage::takeScreenshot(const QString & mail = "" ) {
    QString output;
    QStringList arguments;
    arguments << mail;
    return system("/usr/local/bin/screenshot.sh", arguments, output);
}

bool WebPage::loadURL(const QString link){
    // No need for network test, will be done in urlChanged
    b->loadurl(QUrl(link));
    return true;
}

bool WebPage::clearCache(){
    QWebSettings::clearMemoryCaches();
    qApp->processEvents();
    return true;
}

//
// Auxiliary
//

bool WebPage::system(const QString& command, const QStringList& arguments, QString& output) {
    // Set-up the process
    qDebug() << "DEBUG: executing system command" << command << "with arguments" << arguments.join(" ");
    QProcess process(this);
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.start(command, arguments);

    // Wait for the end of the command
    QEventLoop loop;
    connect(&process, SIGNAL(finished(int, QProcess::ExitStatus)), &loop, SLOT(quit()));
    loop.exec();

    // Return appropriate data
    output = process.readAll();
    return (process.exitStatus() == QProcess::NormalExit);
}

bool WebPage::sudo(const QStringList& arguments, QString& output) {
    return system("/usr/bin/sudo", arguments, output);
}

