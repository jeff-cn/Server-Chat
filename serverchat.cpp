#include "serverchat.h"
#include <QThread>
#include <QDebug>

ServerChat::ServerChat(qint64 port)
{
    this->listen(QHostAddress::Any, port);
    if(this->isListening()){
        qDebug() << "Server listening!";
    }else{
        qDebug() << "Error server start!";
    }

    _thread = new QThread();
    wrapper = new Wrapper();
    wrapper->moveToThread(_thread);
    connect(this, &ServerChat::signalCreateNewClient, wrapper, &Wrapper::slotNewClient,Qt::QueuedConnection);
    connect(wrapper, &Wrapper::signalAppendUserInList, this, &ServerChat::appendUserInList);
    _thread->start();
}

ServerChat::~ServerChat()
{
    _thread->terminate();
    delete _thread;
}

void ServerChat::incomingConnection(qintptr socketDescriptor)
{
    emit signalCreateNewClient(socketDescriptor);
    qDebug() << "New client.";
}

void ServerChat::slotSendMessageToClients(QString msg)
{
    qDebug() << msg;
    for(int i = 0; i < clientsList.size(); i++){
        clientsList[i]->sendMessageClient(msg);
    }
}

void ServerChat::appendUserInList(Client *c)
{
    clientsList.append(c);
    connect(c, &Client::sendMessageToServer, this, &ServerChat::slotSendMessageToClients);
}
