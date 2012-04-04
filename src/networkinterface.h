//
// Configuration
//

// Include guard
#ifndef NETWORKINTERFACE_H
#define NETWORKINTERFACE_H

// Library includes
#include <QtCore/QObject>
#include <QtCore/QSettings>
#include <QtGui/QMainWindow>

// Local includes
#include "qexception.h"

namespace FlatTurtle {
    class NetworkInterface : public QObject {
    Q_OBJECT
    public:
        // Construction and destruction
        NetworkInterface(QObject *parent = 0) throw(QException);

    private:
        // Member objects
        QSettings *mSettings;
    };
}

#endif // NETWORKINTERFACE_H
