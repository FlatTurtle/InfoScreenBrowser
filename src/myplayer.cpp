#include "myplayer.h"
#include <QUrl>

MyPlayer::MyPlayer(QWidget *parent) : Phonon::VideoPlayer(Phonon::VideoCategory, parent)
{
}

MyPlayer::MyPlayer(const MyPlayer &): Phonon::VideoPlayer(0)
{
}

void MyPlayer::replay(void){
    this->mediaObject()->clear();
    this->play(QUrl::fromLocalFile(current));
}

void MyPlayer::playfile(QString file){
    qDebug() << "Playing: " << file;
    current = file;
    this->mediaObject()->clear();
    this->play(QUrl::fromLocalFile(current));
}
