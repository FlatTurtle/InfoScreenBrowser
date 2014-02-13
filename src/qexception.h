#ifndef EXCEPTION_H
#define EXCEPTION_H

// Library includes
#include <QtCore/QString>

class QException
{
public:
    QException(const QString& message) throw() : mMessage(message) {
    }

    const QString& what() const {
        return mMessage;
    }

private:
    QString mMessage;
};

#endif // EXCEPTION_H

