#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QByteArray>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client();
    ~Client();

    void sendMessageClient(QString &msg);
    void initialization(qintptr socketDescriptor);

signals:
    void signalStopThread();
    void sendMessageToServer(QString msg);
    void signalWriteByteInSocket(const QByteArray&);

public slots:
    void readMessage();
    void clientDiskonnect();

private slots:
    void slotWriteByteInSocket(const QByteArray &b);

private:
    QTcpSocket *clientSocket;
    quint16 nextBlockSize;
};

#endif // CLIENT_H
