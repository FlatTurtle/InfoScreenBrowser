#ifndef NETWORKINTERFACE_H
#define NETWORKINTERFACE_H

// Library includes
#include <QtCore/QObject>
#include <QtCore/QSettings>
#include <QtGui/QMainWindow>
#include <qxmpp/QXmppClient.h>
#include <qxmpp/QXmppMessage.h>
#include <qjson/serializer.h>

// Local includes
#include "qexception.h"
#include "browser.h"

class NetworkInterface : public QXmppClient {
    Q_OBJECT
public:
    // Construction and destruction
    NetworkInterface(QObject *parent) throw(QException);

    // XMPP events
private slots:
    void messageReceived(const QXmppMessage& message);
    void disconnected();
    void connected();

private:
    // Member objects
    QJson::Serializer jsonSerializer;
    // parent Browser
    Browser *b;
};

#endif // NETWORKINTERFACE_H

