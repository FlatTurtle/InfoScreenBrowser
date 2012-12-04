#ifndef MY_PLAYER_H
#define MY_PLAYER_H

#include <QMetaType>
#include <phonon/videoplayer.h>
#include <phonon/mediaobject.h>
#include <phonon/videowidget.h>

class MyPlayer: public Phonon::VideoPlayer
{
   Q_OBJECT
   public:
      MyPlayer(QWidget *parent = 0);
	  QString current;
      // Q_DECLARE_METATYPE requires a copy-constructor
      MyPlayer(const MyPlayer &copy);
   public slots:
       void replay(void);
	   void playfile(QString);

};
Q_DECLARE_METATYPE(MyPlayer)


#endif
