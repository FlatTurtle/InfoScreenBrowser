#include "myplayer.h"
#include <QUrl>

MyPlayer::MyPlayer(QWidget *parent) : Phonon::VideoPlayer(Phonon::VideoCategory, parent)
{
	connect(this, SIGNAL(finished()), this, SLOT(replay()));
}

MyPlayer::MyPlayer(const MyPlayer &): Phonon::VideoPlayer(0)
{
}

void MyPlayer::replay(void){
	this->play(QUrl::fromLocalFile(current));
}

void MyPlayer::test(void){
	qDebug() << "Testing...";
}

void MyPlayer::playfile(QString file){
	qDebug() << "Playing: " << file;
	current = file;
	this->play(QUrl::fromLocalFile(current));
}
