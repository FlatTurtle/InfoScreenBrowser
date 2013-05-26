//
// Configuration
//

// Include guard
#ifndef BROWSER_H
#define BROWSER_H

// Library includes
#include <QtCore/QStringList>
#include <QtWebKit/QWebView>
#include <QtWebKit/QWebPage>

namespace FlatTurtle
{
    class WebPage : public QWebPage
    {
    Q_OBJECT
    public:
        // Construction and destruction
        WebPage(QWidget *iParent = 0);

        // WebPage interface
        QString userAgentForUrl(const QUrl &iUrl) const;
        void setUserAgent(const QString &str);
        void javaScriptConsoleMessage(const QString &iMessage, int iLineNumber, const QString &iSourceId);
    public slots:
        bool shouldInterruptJavaScript();

        // Application interface
    public slots:
        bool reboot();
        bool puppetUpdate();
        bool enableScreen(bool iEnabled);
        bool soundControl(const QString &cmd);
        bool takeScreenshot(const QString &mail);

    private:

        // Auxiliary
        bool system(const QString& iCommand, const QStringList& iArguments, QString& oOutput);
        bool sudo(const QStringList& iArguments, QString& oOutput);
        QObject* createPlugin(const QString&, const QUrl&, const QStringList&, const QStringList&);

        // Member data
        QString mUserAgent;
    };

    class Browser : public QObject
    {
    Q_OBJECT
    public:
        // Construction and destruction
        Browser(QObject *iParent = 0);

        // Infoscreen interface
        QWebView *view();
        QVariant execute(const QString& iCode);
		
    public slots:
        void urlChanged ( const QUrl & url );
        void clearCache();

        // Data members
    private:
        QWebView *mWebView;
    };
}
#endif // BROWSER_H
