#ifndef ROBOTSENSORS_H
#define ROBOTSENSORS_H

#include <QString>
#include <QChar>

#include <QObject>

#include <QDebug>

#include "serialworker.h"

using namespace std;

//IR Front Right = 0
//IR Front Left = 1
//IR Back Right = 2
//IR Back Left = 3

enum IR_SENSORS {
    IR_FRONT_RIGHT = 0,
    IR_FRONT_LEFT = 1,
    IR_BACK_RIGHT = 2,
    IR_BACK_LEFT = 3,
};

class RobotSensors: public QObject
{
    Q_OBJECT

public:
    RobotSensors();

    double GetIRValue(int);
    double GetIRValue(IR_SENSORS);

    static const double ROCK_LIMIT = 0.2;
    static const double CRATER_LIMIT = 0.4;

private:
    void InterpretDataType(string);
    void ParseSingleData(string, vector<int>&);

    vector<double> irValues;

    SerialWorker serialConnection;

    static const string SERIAL_PORT;

    static const int NUM_IR_SENSORS = 4;

public slots:
    void ParseString(QString);

signals:
    void SendData(QString);
};

#endif // ROBOTSENSORS_H
