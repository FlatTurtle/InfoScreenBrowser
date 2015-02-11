#include "browser.h"
#include <QApplication>

#include "myplayer.h"

int main(int argc, char *argv[])
{
    // Video player object meta type
    qRegisterMetaType<MyPlayer>("MyPlayer");

    QApplication a(argc, argv);
    
    // Configure the application
    a.setOrganizationName("FlatTurtle");
    a.setOrganizationDomain("FlatTurtle.com");
    a.setApplicationName("InfoScreenBrowser");
    a.setApplicationVersion("2.1");
    
    // Launch the bowser
    Browser w;
    w.show();

    return a.exec();
}
