// Local includes
#include "networkinterface.h"

// Library includes
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <QtCore/QTimer>
#include <QtNetwork/QHostInfo>
#include <qxmpp/QXmppConfiguration.h>
#include <qxmpp/QXmppRosterManager.h>
#include <QDir>

NetworkInterface::NetworkInterface(QObject *parent) throw(QException)
    : QXmppClient(parent) {

    // Connect slots
    connect(this, SIGNAL(messageReceived(const QXmppMessage&)), SLOT(messageReceived(const QXmppMessage&)));
    connect(this, SIGNAL(disconnected()), SLOT(disconnected()));
    connect(this, SIGNAL(connected()), SLOT(connected()));

    QSettings settings(QString(QDir::homePath() + "/.infoscreenbrowser"), QSettings::IniFormat);
    QString host = settings.value("xmpp/host", "xmpp.corp.flatturtle.com").toString();
    QString resource = settings.value("xmpp/resource", "botnet.corp.flatturtle.com").toString();

    b = (Browser *)parent;

    // Construct the configuration parameters
    QXmppConfiguration configuration;
    configuration.setHost(host);
#ifdef DEVEL
    qWarning() << "WARNING: using development XMPP configuration";
    configuration.setResource(resource);
    configuration.setJid("testclient@"+resource);
#else
    QHostInfo hostInfo;
    configuration.setResource(resource);
    configuration.setJid(hostInfo.localHostName() + "@" + resource);
    qDebug() << "DEBUG: connecting with JIT" << hostInfo.localHostName() + "@" + resource;
#endif
    configuration.setAutoAcceptSubscriptions(true);
    configuration.setAutoReconnectionEnabled(true);

    // Connect
    connectToServer(configuration);
}


//
// XMPP events
//

void NetworkInterface::messageReceived(const QXmppMessage& message) {
    qDebug() << "Received command from" << message.from() << ":" << message.body();
    QVariant output = b->execute(message.body());
    sendMessage(message.from(), jsonSerializer.serialize(output));
}

void NetworkInterface::disconnected() {
    qWarning() << "WARNING: attempting to reconnect";
    // FIXME: this is necessary becuase the ReconnectionManager doesn't reconnect
    //        if the client got forcibly disconnected
    connectToServer(configuration(), clientPresence());
    // FIXME: no reconnection timer necessary? Handled by ReconnectionManager?
}

void NetworkInterface::connected() {
    // Subscribe to the admin
    // TODO: use subscribe() in qxmpp 4.0
    qDebug() << "DEBUG: connected";
    QXmppPresence presence(QXmppPresence::Subscribe);
    QSettings settings(QString(QDir::homePath() + "/.infoscreenbrowser"), QSettings::IniFormat);
    QString adminaccount = settings.value("xmpp/admin", "admin@botnet.corp.flatturtle.com").toString();

    presence.setTo(adminaccount);
    sendPacket(presence);
}

