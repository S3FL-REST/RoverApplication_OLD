#ifndef SERIALWORKER_H
#define SERIALWORKER_H

#include <QObject>
#include <QTimer>
#include <QString>
#include <QCoreApplication>

#include <QDebug>
#include <QThread>

#include <string>

#include "serialconnection.h"

using namespace std;

class SerialWorker : public QObject
{
    Q_OBJECT
public:
    SerialWorker(string);
    bool IsConnected();
    ~SerialWorker();

protected:
    SerialConnection serialCon;
    QTimer timer;
    string port;

private:
    QThread* mThread;

signals:
    void ReceivedData(QString);
    void SendDataToSerial(QString);

public slots:
    void GetData();
    void SendData(QString);

private slots:
    void Start();
    void Stop();
    void StopThread();
};

#endif // SERIALWORKER_H
