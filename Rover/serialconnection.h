#ifndef SERIALCONNECTION_H
#define SERIALCONNECTION_H

#include <QObject>
#include <QThread>

#include <string>
#include <SerialStream.h>
#include <SerialStreamBuf.h>

#include <vector>

#include <QDebug>

using namespace std;
using namespace LibSerial;

class SerialConnection : public QObject
{
    Q_OBJECT
public:
    SerialConnection();
    void Connect(string port);
    void Close();

    string GetData();
    bool IsConnected();

private:
    SerialStream serial;
    string currentData;
    vector<string> previousCommands;

    int currentLostCount;

    static const int MAX_LOST_COUNT;

signals:

public slots:
    void SendData(QString);
};

#endif // SERIALCONNECTION_H
