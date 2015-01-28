#ifndef SERIALCONNECTION_H
#define SERIALCONNECTION_H

#include <QObject>
#include <QThread>

#include <QString>

#include <vector>

#include <SerialStream.h>

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

    QString GetData();
    bool IsConnected();

private:
    SerialStream serial;
    QString currentData;
    QStringList dataList;

    int currentLostCount;

    static const int MAX_LOST_COUNT;

signals:

public slots:
    void SendData(QString);
};

#endif // SERIALCONNECTION_H
