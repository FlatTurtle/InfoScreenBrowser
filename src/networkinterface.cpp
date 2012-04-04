//
// Configuration
//

// Local includes
#include "networkinterface.h"
#include "mainapplication.h"

// Library includes
#include <QtCore/QStringList>
#include <QtCore/QDebug>


//
// Construction and destruction
//

FlatTurtle::NetworkInterface::NetworkInterface(QObject *iParent) throw(QException)
    : QObject(iParent) {
    // Load settings
    mSettings = new QSettings(this);
    mSettings->beginGroup(metaObject()->className());
}
