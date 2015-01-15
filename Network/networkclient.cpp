#include "networkclient.h"

const int NetworkClient::port = 3141;

NetworkClient::NetworkClient() : server(this), socket(0) {
    bool listening = server.listen(QHostAddress::Any, port);
    if (!listening) qDebug() << "Server failed to start";

    connect(&server, SIGNAL(newConnection()), this, SLOT(NewConnection()));

    mThread = new QThread(this);
    this->moveToThread(mThread);
    mThread->start();
}

void NetworkClient::NewConnection() {
    if (socket == 0 || !socket->isOpen()) {
        socket = server.nextPendingConnection();
        qDebug() << "Accepted Conenction from " << socket->localAddress().toString();

        connect(socket, SIGNAL(readyRead()), this, SLOT(DataReady()));
        connect(socket, SIGNAL(disconnected()), this, SLOT(SocketDisconnected()));
        connect(socket, SIGNAL(disconnected()), socket, SLOT(deleteLater()));
    } else {
        qDebug() << "Server Already Connected";
    }
}

void NetworkClient::SocketDisconnected() {
    qDebug() << "Socket " << socket->localAddress().toString() << " Disconnected";
    socket = 0;
    emit ConnectionLost();
}

void NetworkClient::DataReady() {
    QByteArray data = "";

    while (socket->bytesAvailable()) {
        data += socket->readAll();
    }

    emit DataReceived(data);
}
