#ifndef NETWORKCLIENT_H
#define NETWORKCLIENT_H

#include <QObject>

#include <QTcpServer>
#include <QTcpSocket>
#include <QThread>

#include <QDebug>

class NetworkClient : public QObject
{
    Q_OBJECT
public:
    NetworkClient();

    bool IsConnected();

private:
    QTcpServer server;
    QTcpSocket *socket;
    QThread *mThread;

    static const int port;

signals:
    void DataReceived(QByteArray);
    void ConnectionLost();

public slots:
    void NewConnection();

private slots:
    void SocketDisconnected();
    void DataReady();
};

#endif // NETWORKCLIENT_H
