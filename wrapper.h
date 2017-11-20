#ifndef WRAPPER_H
#define WRAPPER_H

#include <QObject>
#include "client.h"

class Wrapper : public QObject
{
    Q_OBJECT
public:
    explicit Wrapper(QObject *parent = 0);

signals:
   void signalAppendUserInList(Client*);

public slots:
    void slotNewClient(qintptr socketDescriptor);
};

#endif // WRAPPER_H
