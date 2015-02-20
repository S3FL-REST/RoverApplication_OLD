#ifndef ROBOTDATA_H
#define ROBOTDATA_H

#include <QString>
#include <QObject>

#include <QDebug>

#include "serialworker.h"

using namespace std;

class RobotData: public QObject
{
    Q_OBJECT

public:
    RobotData();

private:
    SerialWorker serialConnection;

    static const string SERIAL_PORT;

public slots:
    void ParseString(QString);

signals:
    void SendData(QString);
};

#endif // ROBOTDATA_H
