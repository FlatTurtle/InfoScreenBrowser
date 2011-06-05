//
// Configuration
//

// Include guard
#ifndef BROWSER_H
#define BROWSER_H

// Library includes
#include <QtWebKit/QWebView>
#include <QtWebKit/QWebPage>

namespace iRail
{
    class WebPage : public QWebPage
    {
    Q_OBJECT
    public:
        // Construction and destruction
        WebPage(QWidget *parent = 0);

        // WebPage interface
        QString userAgentForUrl(const QUrl &iUrl) const;
        void javaScriptConsoleMessage(const QString& iMessage, int iLineNumber, const QString& iSourceId);
    };

    class Browser : public QObject
    {
    Q_OBJECT
    public:
        // Construction and destruction
        Browser(QObject *parent = 0);

        // Infoscreen interface
        QWebView* view();
        void start();

        // UI slots
    private slots:
        void onLoadStarted();
        void onLoadProgress(int progress);
        void onLoadFinished(bool ok);

        // Data members
    private:
        QWebView* mWebView;
    };
}
#endif // BROWSER_H
