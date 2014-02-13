#ifndef NETWORKTEST_H
#define NETWORKTEST_H

#include <QObject>
#include <QNetworkReply>
#include <QEventLoop>

class NetWorkTest : public QObject
{
    Q_OBJECT

public:
    explicit NetWorkTest(QObject *parent = 0);
    void checkSite(QString url);

private:
    QNetworkAccessManager *manager;
    QEventLoop *loop;
    int status;

signals:
    
public slots:
    void replyFinished(QNetworkReply  *);
    
};

#endif // NETWORKTEST_H

