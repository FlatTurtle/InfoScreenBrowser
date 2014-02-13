#ifndef WEBPAGE_H
#define WEBPAGE_H

// Library includes
#include <QtCore/QStringList>
#include <QtWebKit/QWebView>
#include <QtWebKit/QWebPage>

// Local includes
#include "browser.h"

class WebPage : public QWebPage
{
    Q_OBJECT
public:
    // Construction and destruction
    WebPage(QWidget *parent);

    // WebPage interface
    QString userAgentForUrl(const QUrl &) const;
    void setUserAgent(const QString &str);
    void javaScriptConsoleMessage(const QString &message, int lineNumber, const QString &sourceId);

public slots:
    bool shouldInterruptJavaScript();

// Application interface
public slots:
    bool reboot();
    bool clearCache();
    bool puppetUpdate();
    bool enableScreen(bool enabled);
    bool soundControl(const QString &cmd);
    bool takeScreenshot(const QString &mail);
    bool loadURL(const QString link);

private:
    // Auxiliary
    bool system(const QString& command, const QStringList& arguments, QString& output);
    bool sudo(const QStringList& arguments, QString& output);
    QObject* createPlugin(const QString&, const QUrl&, const QStringList&, const QStringList&);

    // Member data
    QString useragent;
    Browser *b;

private slots:
    void populateJavaScriptWindowObject();

};

#endif // WEBPAGE_H

