#ifndef SERIALWORKER_H
#define SERIALWORKER_H

#include <QObject>
#include <QTimer>

#include <QDebug>
#include <QThread>

#include <string>
#include <QString>

#include "serialconnection.h"

using namespace std;

class SerialWorker : public QObject
{
    Q_OBJECT
public:
    SerialWorker(string);
    void moveToThread(QThread *thread);
    bool IsConnected();
    ~SerialWorker();

    static void StartWorker(SerialWorker*);
    static void StopWorker(SerialWorker*);

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
};

#endif // SERIALWORKER_H
