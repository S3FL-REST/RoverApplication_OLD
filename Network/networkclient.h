#ifndef NETWORKCLIENT_H
#define NETWORKCLIENT_H

#include <QObject>

#include <QTcpServer>
#include <QTcpSocket>
#include <QThread>

#include <QDebug>

#include "Protocols/rest_network.pb.h"

using namespace rest_network;

class NetworkClient : public QObject
{
    Q_OBJECT
public:
    NetworkClient();

private:
    QTcpServer server;
    QTcpSocket *socket;
    QThread *mThread;

    static const int port;

signals:
    void DataReceived(QByteArray);

public slots:
    void NewConnection();

private slots:
    void SocketDisconnected();
    void DataReady();
};

#endif // NETWORKCLIENT_H
