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

// Local includes
#include "qexception.h"
#include "browser.h"

namespace FlatTurtle {
    class UserInterface : public QMainWindow {
    Q_OBJECT
    public:
        // Construction and destruction
        UserInterface(QWidget *iParent = 0) throw(QException);

        // Functionality
        void execute(const QString& iCode);

    private:
        // Member objects
        QSettings *mSettings;
        Browser *mBrowser;
    };
}

#endif // USERINTERFACE_H
