
#include "browser.h"
Browser::Browser() : QWebView() {
}
QString webPage::userAgentForUrl(const QUrl &url ) const {
        return QString("test user agent");
}
webPage::webPage() : QWebPage() {
}
