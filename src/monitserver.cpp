#include "monitserver.h"
#include "monitserverthread.h"

#include <stdlib.h>

MonitServer::MonitServer(QObject *parent)
    : QTcpServer(parent)
{
	flag = 0;
}

void MonitServer::incomingConnection(int socketDescriptor)
{
	flag = 1;
    MonitServerThread *thread = new MonitServerThread(socketDescriptor, this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}
