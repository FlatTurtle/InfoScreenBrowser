//
// Configuration
//

// Include guard
#ifndef USERINTERFACE_H
#define USERINTERFACE_H

// Library includes
#include <QtCore/QObject>
#include <QtCore/QSettings>
#include <QtGui/QMainWindow>
#include <QtWebKit/QWebView>

// Local includes
#include "qexception.h"

namespace iRail
{
    class UserInterface : public QMainWindow
    {
    Q_OBJECT
    public:
        // Construction and destruction
        UserInterface(QWidget *parent = 0) throw(QException);

        // Messaging methods
        void showNotice(const QString& iMessage) const;
        void showAlert(const QString& iMessage) const;

    private:
        // Member objects
        QSettings *mSettings;
        QWebView *mWebView;
    };
}

#endif // USERINTERFACE_H
