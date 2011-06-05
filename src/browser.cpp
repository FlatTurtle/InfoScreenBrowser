//
// Configuration
//

// Local includes
#include "browser.h"

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

Browser::Browser(QWidget* parent) : QWebView(parent)
{
}

WebPage::WebPage() : QWebPage()
{

}


//
// Infoscreen interface
//

void Browser::start()
{
    setPage((QWebPage*) new WebPage());
    load(QUrl("http://infoscreen.flatturtle.com/"));
}


//
// WebPage interface
//

QString WebPage::userAgentForUrl(const QUrl &iUrl) const
{
        return QString("irail-infoscreen");
}
