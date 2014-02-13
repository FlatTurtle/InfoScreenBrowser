#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QDebug>
#include <QEventLoop>

#include "networktest.h"

#ifdef Q_OS_WIN
#include <windows.h> // for Sleep
#endif
void mysleep(int ms)
{

#ifdef Q_OS_WIN
    Sleep(uint(ms));
#else
    #include <time.h>
    struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
    nanosleep(&ts, NULL);
#endif
}

NetWorkTest::NetWorkTest(QObject *parent) :
    QObject(parent)
{

}

void NetWorkTest::checkSite(QString url) {
  QUrl qrl(url);
  manager = new QNetworkAccessManager(this);
  loop = new QEventLoop();

  connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

  status = -1;

  while(status != 0){
    mysleep(5000);
    manager->get(QNetworkRequest(qrl));
    loop->exec();
  }

}

void NetWorkTest::replyFinished(QNetworkReply  *reply){
    status = reply->error();
    //QString answer = QString::fromUtf8(reply->readAll());
    emit loop->quit();
}

