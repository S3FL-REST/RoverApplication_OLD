#ifndef ROBOTDATA_H
#define ROBOTDATA_H

#include <vector>
#include <string>
#include <sstream>
#include <stdlib.h>

#include <QString>
#include <QObject>

#include <QDebug>

#include "serialworker.h"

using namespace std;

enum IR_SENSORS {
    F_R = 0,
    F_L = 1,
    B_R = 1,
    B_L = 1,
};

class RobotData: public QObject
{
    Q_OBJECT

public:
    RobotData();

    double GetIRValue(int);

    void SetMotorValues(int, int);

private:
    vector<double> irValues;

    SerialWorker serialConnection;

    static const string SERIAL_PORT;

    static const int NUM_IR_SENSORS = 4;

    static const double ROCK_LIMIT = 0.2;
    static const double CRATER_LIMIT = 0.4;

public slots:
    void ParseString(QString);

signals:
    void SendData(QString);
};

#endif // ROBOTDATA_H
