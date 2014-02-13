#include "browser.h"
#include "ui_browser.h"

#include "networkinterface.h"
#include "networktest.h"
#include "webpage.h"

// Library includes
#include <QHostInfo>

Browser::Browser(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Browser)
{
    ui->setupUi(this);

    QSettings settings(QString(QDir::homePath() + "/.infoscreenbrowser"), QSettings::IniFormat);
    bool pluginsEnabled = settings.value("browser/pluginsenabled", true).toBool();
    if(pluginsEnabled){
        QWebSettings::globalSettings()->setAttribute(QWebSettings::PluginsEnabled, true);
    }

    QWebSettings::setMaximumPagesInCache(1);

    // Check connectivity, and keep trying
    NetWorkTest *t = new NetWorkTest();
    t->checkSite("https://data.flatturtle.com");
    delete t;

    // The main webview widget 
    view = new QWebView();

    // Our subclassed webpage 
    view->setPage(new WebPage(this));


#ifdef DEVEL
    qWarning() << "WARNING: using development infoscreen";
    loadurl(QUrl("https://go.flatturtle.com/"));
#else
    QHostInfo info;
    loadurl(QUrl("https://go.flatturtle.com/" + info.localHostName()));
#endif

    ui->gridLayout->addWidget(view);

    bool fullscreen = settings.value("browser/fullscreen", false).toBool();
    if(fullscreen){
        showFullScreen();
    }

    connect(view,SIGNAL(urlChanged(const QUrl)), this, SLOT(urlChanged (const QUrl)));

    // Network Interface
    n = new NetworkInterface(this);

}

Browser::~Browser()
{
    delete ui;
}

void Browser::loadurl(const QUrl &url){
    view->load(QUrl(url));
}

void Browser::urlChanged(const QUrl &url){

    static QUrl tmp;

    if(tmp != url){
        NetWorkTest *t = new NetWorkTest();
        t->checkSite("https://data.flatturtle.com");
        delete t;
        view->load(QUrl(url));
        tmp = url;
    }
}


QVariant Browser::execute(const QString& code) {
    return view->page()->mainFrame()->evaluateJavaScript(code);
}

