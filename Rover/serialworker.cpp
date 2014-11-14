#include "serialworker.h"

SerialWorker::SerialWorker(string port) : serialCon(), timer(this), port(port) {
    connect(&timer, SIGNAL(timeout()), this, SLOT(GetData()));

    connect(this, SIGNAL(SendDataToSerial(QString)), &serialCon, SLOT(SendData(QString)));

    mThread = new QThread;
    moveToThread(mThread);
    mThread->start();
}

void SerialWorker::moveToThread(QThread *thread) {
    QObject::moveToThread(thread);
    serialCon.moveToThread(thread);
}

void SerialWorker::Start() {
    if (serialCon.IsConnected()) serialCon.Close();
    serialCon.Connect(port);
    timer.start(50);
}

void SerialWorker::StartWorker(SerialWorker* worker) {
    QMetaObject::invokeMethod(worker, "Start", Qt::QueuedConnection);
}

void SerialWorker::GetData() {
    if (serialCon.IsConnected()) {
        emit ReceivedData(serialCon.GetData().c_str());
    }
    else {
        serialCon.Close();

        while (!serialCon.IsConnected()) {
            if (0 == access(port.c_str(), 0)) {
                serialCon.Connect(port);
            } else {
                qDebug() << "Connection Lost";
                usleep(1000000);
            }
        }
    }
}

void SerialWorker::SendData(QString data) {
    emit SendDataToSerial(data);
}

bool SerialWorker::IsConnected() {
    return serialCon.IsConnected();
}

void SerialWorker::Stop() {
    serialCon.Close();
    if (timer.isActive()) timer.stop();
}

void SerialWorker::StopWorker(SerialWorker* worker) {
    QMetaObject::invokeMethod(worker, "Stop", Qt::QueuedConnection);
}

SerialWorker::~SerialWorker() {
    mThread->quit();
    delete mThread;
}
