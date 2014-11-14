#ifndef ROBOTDATA_H
#define ROBOTDATA_H

#include <vector>
#include <string>
#include <sstream>
#include <stdlib.h>

#include <QString>
#include <QObject>

#include <QDebug>

using namespace std;

class RobotData: public QObject
{
    Q_OBJECT

public:
    RobotData();
    void Print(ostream&);

private:
    void InterpretDataType(string);
    void ParseSingleData(string, vector<int>&);

    vector<int> encoderValues;
    vector<int> irValues;
    vector<int> imuValues;

    static const int NUM_ENCODERS = 4;
    static const int NUM_IR_SENSORS = 4;
    static const int NUM_IMU_DATA = 9;

public slots:
    void ParseString(QString);
};

#endif // ROBOTDATA_H
