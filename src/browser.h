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
    public:
        // Construction and destruction
        WebPage();

        // WebPage interface
        QString userAgentForUrl(const QUrl &iUrl) const;
    };

    class Browser : public QWebView
    {
    public:
        // Construction and destruction
        Browser(QWidget *parent = 0);

        // Infoscreen interface
        void start();
    };
}
#endif // BROWSER_H
