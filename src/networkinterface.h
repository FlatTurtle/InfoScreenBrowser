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
#include <qxmpp/QXmppClient.h>
#include <qxmpp/QXmppMessage.h>

// Local includes
#include "qexception.h"

namespace FlatTurtle {
    class NetworkInterface : public QXmppClient {
    Q_OBJECT
    public:
        // Construction and destruction
        NetworkInterface(QObject *parent = 0) throw(QException);

        // XMPP events
    private slots:
        void messageReceived(const QXmppMessage& iMessage);

    private:
        // Member objects
        QSettings *mSettings;
    };
}

#endif // NETWORKINTERFACE_H
