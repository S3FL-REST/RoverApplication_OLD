#include "networkclient.h"

#include <QCoreApplication>

const int NetworkClient::port = 3141;

NetworkClient::NetworkClient() : server(), socket() {

    mThread = new QThread(this);
    this->moveToThread(mThread);

    mThread->start();

    bool listening = server.listen(QHostAddress::Any, port);
    if (!listening) qDebug() << "Server failed to start";
    connect(&server, SIGNAL(newConnection()), this, SLOT(NewConnection()));

    connect(mThread, SIGNAL(finished()), mThread, SLOT(deleteLater()));
}

bool NetworkClient::IsConnected() {
    return socket != NULL;
}

void NetworkClient::NewConnection() {
    if (socket == 0 || !socket->isOpen()) {
        socket = server.nextPendingConnection();
        qDebug() << "Accepted Conenction from " << socket->localAddress().toString();

        connect(socket, SIGNAL(readyRead()), this, SLOT(DataReady()));
        connect(socket, SIGNAL(disconnected()), this, SLOT(SocketDisconnected()));
    } else {
        qDebug() << "Server Already Connected";
    }
}

void NetworkClient::SocketDisconnected() {
    qDebug() << "Socket " << socket->localAddress().toString() << " Disconnected";

    socket->close();

    disconnect(socket, SIGNAL(readyRead()), this, SLOT(DataReady()));
    disconnect(socket, SIGNAL(disconnected()), this, SLOT(SocketDisconnected()));

    delete socket;
    socket = NULL;

    emit ConnectionLost();
}

void NetworkClient::DataReady() {
    QByteArray data = "";

    while (socket->bytesAvailable())
        data += socket->readAll();

    emit DataReceived(data);
}

NetworkClient::~NetworkClient() {
    disconnect(&server, SIGNAL(newConnection()), this, SLOT(NewConnection()));

    server.close();
    socket->close();
    delete socket;

    mThread->quit();
    delete mThread;
}
