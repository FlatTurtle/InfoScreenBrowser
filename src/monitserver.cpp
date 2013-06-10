#include "monitserver.h"
#include "monitserverthread.h"

#include <stdlib.h>

MonitServer::MonitServer(QObject *parent)
    : QTcpServer(parent)
{
}

void MonitServer::incomingConnection(int socketDescriptor)
{
    MonitServerThread *thread = new MonitServerThread(socketDescriptor, this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}
