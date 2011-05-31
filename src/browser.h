#ifndef BROWSER_H
#define BROWSER_H

#include <QWebView>
#include <QWebPage>

class webPage : public QWebPage {
        public: webPage();
        QString userAgentForUrl(const QUrl &url ) const;
};
class Browser : public QWebView {
        public: Browser();
};
#endif // BROWSER_H
