#ifndef MONITSERVER_H
#define MONITSERVER_H

#include <QTcpServer>

class MonitServer : public QTcpServer
{
    Q_OBJECT

public:
    MonitServer(QObject *parent = 0);
	int flag;
protected:
    void incomingConnection(int socketDescriptor);

};

#endif // MONITSERVER_H
