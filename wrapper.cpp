#include "wrapper.h"
#include <QThread>

Wrapper::Wrapper(QObject *parent) : QObject(parent)
{

}

void Wrapper::slotNewClient(qintptr socketDescriptor)
{
    Client *client = new Client();
    client->initialization(socketDescriptor);
    emit signalAppendUserInList(client);
}
