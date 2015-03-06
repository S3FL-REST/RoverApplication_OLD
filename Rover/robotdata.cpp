#include "robotdata.h"

//Temperature Filepath: /sys/class/thermal/thermal_zone0/temp

const string RobotData::SERIAL_PORT("/dev/ttyACM1");

RobotData::RobotData() : serialConnection(SERIAL_PORT) {

    //Connect signals and slots for serial object
    connect(this, SIGNAL(SendData(QString)), &serialConnection, SLOT(SendData(QString)));
    connect(&serialConnection, SIGNAL(ReceivedData(QString)), this, SLOT(ParseString(QString)));
}

void RobotData::ParseString(QString data) {
    if (data.size() == 0) return;
}
