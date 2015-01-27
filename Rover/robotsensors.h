#ifndef ROBOTSENSORS_H
#define ROBOTSENSORS_H

#include <QObject>
#include <vector>
#include <string>
#include <sstream>
#include <stdlib.h>

#include <QString>
#include <QObject>

#include <QDebug>

#include "serialworker.h"

using namespace std;

class RobotSensors: public QObject
{
    Q_OBJECT

public:
    RobotSensors();

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

#endif // ROBOTSENSORS_H
