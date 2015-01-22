#include "robotdata.h"

//Temperature Filepath: /sys/class/thermal/thermal_zone0/temp

const string RobotData::SERIAL_PORT("/dev/ttyACM0");

RobotData::RobotData() : irValues(NUM_IR_SENSORS), serialConnection(SERIAL_PORT) {

    //Connect signals and slots for serial object
    connect(this, SIGNAL(SendData(QString)), &serialConnection, SLOT(SendData(QString)));
    connect(&serialConnection, SIGNAL(ReceivedData(QString)), this, SLOT(ParseString(QString)));

    //Start the robotSerial thread
    SerialWorker::StartWorker(&serialConnection);
}

//Parses a formatted string into sensor data objects
void RobotData::ParseString(QString data) {
    if (data.size() == 0) return;
}

double RobotData::GetIRValue(int index) {
    return irValues.at(index);
}

void RobotData::SetMotorValues(int left, int right) {
    emit SendData(QString("D:%1:%2").arg(left, right));
}
