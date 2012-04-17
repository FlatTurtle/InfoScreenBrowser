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
        void javaScriptConsoleMessage(const QString &iMessage, int iLineNumber, const QString &iSourceId);
    public slots:
        bool shouldInterruptJavaScript();

        // Application interface
    public slots:
        bool reboot();
        bool puppetUpdate();
        bool enableScreen(bool iEnabled);

    private:
        // Auxiliary
        bool system(const QString& iCommand, const QStringList& iArguments, QString& oOutput);
        bool sudo(const QStringList& iArguments, QString& oOutput);

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

        // Data members
    private:
        QWebView *mWebView;
    };
}
#endif // BROWSER_H
