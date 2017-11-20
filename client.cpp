#include "client.h"
#include <QDataStream>
#include <QThread>

Client::Client()
{
    nextBlockSize = 0;
    connect(this, &Client::signalWriteByteInSocket, this, &Client::slotWriteByteInSocket);
}

Client::~Client()
{
    clientSocket->close();
    delete clientSocket;
}

void Client::initialization(qintptr socketDescriptor)
{
    clientSocket = new QTcpSocket();
    clientSocket->setSocketDescriptor(socketDescriptor);
    connect(clientSocket, &QTcpSocket::readyRead, this, &Client::readMessage);
    connect(clientSocket, &QTcpSocket::disconnected, this, &Client::clientDiskonnect);
}

void Client::readMessage()
{
    QDataStream in(clientSocket);
    in.setVersion(QDataStream::Qt_5_8);

    while (true) {
        if(!nextBlockSize){
            if(clientSocket->bytesAvailable() < (int)sizeof(quint16)) return;
            in >> nextBlockSize;
        }
        if(clientSocket->bytesAvailable() < nextBlockSize){
            return;
        }else{
            nextBlockSize = 0;
        }
        QString message;
        in >> message;
        emit sendMessageToServer(message);
        break;
    }
}

void Client::clientDiskonnect()
{
    emit signalStopThread();
    clientSocket->close();
    clientSocket->deleteLater();
}

void Client::slotWriteByteInSocket(const QByteArray &b)
{
    clientSocket->write(b);
}

void Client::sendMessageClient(QString &msg)
{
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_8);
    out << quint16(0) << msg;
    out.device()->seek(0);
    out << (quint16)(arrBlock.size() - sizeof(quint16));
    emit signalWriteByteInSocket(arrBlock);
}

