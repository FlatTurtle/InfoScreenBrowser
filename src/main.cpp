#include "browser.h"
#include <QApplication>

#include "myplayer.h"

int main(int argc, char *argv[])
{
    // Video player object meta type
    qRegisterMetaType<MyPlayer>("MyPlayer");

    QApplication a(argc, argv);
    Browser w;
    w.show();

    // Configure the application
    a.setOrganizationName("FlatTurtle");
    a.setOrganizationDomain("FlatTurtle.com");
    a.setApplicationName("InfoScreenBrowser");
    a.setApplicationVersion("1.5");

    return a.exec();
}
