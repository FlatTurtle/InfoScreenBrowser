#ifndef MONITSERVERTHREAD_H
#define MONITSERVERTHREAD_H

#include <QThread>
#include <QTcpSocket>

class MonitServerThread : public QThread
{
    Q_OBJECT

public:
    MonitServerThread(int socketDescriptor, QObject *parent);
    void run();

signals:
    void error(QTcpSocket::SocketError socketError);

private:
    int socketDescriptor;
};

#endif //MONITSERVERTHREAD_H
