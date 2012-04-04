//
// Configuration
//

// Include guard
#ifndef BROWSER_H
#define BROWSER_H

// Library includes
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
    };

    class Browser : public QObject
    {
    Q_OBJECT
    public:
        // Construction and destruction
        Browser(QObject *iParent = 0);

        // Infoscreen interface
        QWebView *view();
        void execute(const QString& iCode);

        // Data members
    private:
        QWebView *mWebView;
    };
}
#endif // BROWSER_H
