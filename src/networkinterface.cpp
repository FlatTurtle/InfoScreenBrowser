//
// Configuration
//

// Local includes
#include "networkinterface.h"
#include "mainapplication.h"

// Library includes
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <QtCore/QTimer>
#include <QtNetwork/QHostInfo>
#include <qxmpp/QXmppConfiguration.h>
#include <qxmpp/QXmppRosterManager.h>
#include <QDir>

//
// Construction and destruction
//

FlatTurtle::NetworkInterface::NetworkInterface(QObject *iParent) throw(QException)
    : QXmppClient(iParent) {
    // Load settings
    mSettings = new QSettings(this);
    mSettings->beginGroup(metaObject()->className());

    // Connect slots
    connect(this, SIGNAL(messageReceived(const QXmppMessage&)), SLOT(messageReceived(const QXmppMessage&)));
    connect(this, SIGNAL(disconnected()), SLOT(disconnected()));
    connect(this, SIGNAL(connected()), SLOT(connected()));

    QSettings settings(QString(QDir::homePath() + "/.infoscreenbrowser"), QSettings::IniFormat);
    QString host = settings.value("xmpp/host", "xmpp.corp.flatturtle.com").toString();
    QString resource = settings.value("xmpp/resource", "botnet.corp.flatturtle.com").toString();

    // Construct the configuration parameters
    QXmppConfiguration tConfiguration;
    tConfiguration.setHost(host);
#ifdef DEVEL
    qWarning() << "WARNING: using development XMPP configuration";
    tConfiguration.setResource(resource);
    tConfiguration.setJid("testclient@"+resource);
#else
    QHostInfo tHostInfo;
    tConfiguration.setResource(resource);
    tConfiguration.setJid(tHostInfo.localHostName() + "@" + resource);
    qDebug() << "DEBUG: connecting with JIT" << tHostInfo.localHostName() + "@" + resource;
#endif
    tConfiguration.setAutoAcceptSubscriptions(true);
    tConfiguration.setAutoReconnectionEnabled(true);

    // Connect
    connectToServer(tConfiguration);
}


//
// XMPP events
//

void FlatTurtle::NetworkInterface::messageReceived(const QXmppMessage& iMessage) {
    qDebug() << "Received command from" << iMessage.from() << ":" << iMessage.body();
    QVariant tOutput = MainApplication::instance()->userInterface()->execute(iMessage.body());
    sendMessage(iMessage.from(), mJsonSerializer.serialize(tOutput));
}

void FlatTurtle::NetworkInterface::disconnected() {
    qWarning() << "WARNING: attempting to reconnect";
    // FIXME: this is necessary becuase the ReconnectionManager doesn't reconnect
    //        if the client got forcibly disconnected
    connectToServer(configuration(), clientPresence());
    // FIXME: no reconnection timer necessary? Handled by ReconnectionManager?
}

void FlatTurtle::NetworkInterface::connected() {
    // Subscribe to the admin
    // TODO: use subscribe() in qxmpp 4.0
    qDebug() << "DEBUG: connected";
    QXmppPresence tPresence(QXmppPresence::Subscribe);
    QSettings settings(QString(QDir::homePath() + "/.infoscreenbrowser"), QSettings::IniFormat);
    QString adminaccount = settings.value("xmpp/admin", "admin@botnet.corp.flatturtle.com").toString();

    tPresence.setTo(adminaccount);
    sendPacket(tPresence);
}
