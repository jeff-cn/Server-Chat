#ifndef SERVERCHAT_H
#define SERVERCHAT_H


#include <QObject>
#include <QTcpServer>
#include <QThread>
#include <QList>
#include "client.h"
#include "wrapper.h"

class ServerChat : public QTcpServer
{
    Q_OBJECT

public:
    ServerChat(qint64 port);
    ~ServerChat();

public slots:
    void slotSendMessageToClients(QString msg);
    void appendUserInList(Client *c);

protected:
    void incomingConnection(qintptr socketDescriptor) override;

signals:
    void signalCreateNewClient(qintptr);

private:
    QList<Client *> clientsList;
    QThread *_thread;
    Wrapper *wrapper;
};

#endif // SERVERCHAT_H
