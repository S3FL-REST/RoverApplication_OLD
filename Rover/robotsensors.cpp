#include "robotsensors.h"

const string RobotSensors::SERIAL_PORT("/dev/ttyACM1");

RobotSensors::RobotSensors() : irValues(NUM_IR_SENSORS), serialConnection(SERIAL_PORT) {
    //Connect signals and slots for serial object
    connect(this, SIGNAL(SendData(QString)), &serialConnection, SLOT(SendData(QString)));
    connect(&serialConnection, SIGNAL(ReceivedData(QString)), this, SLOT(ParseString(QString)));

    //Start the robotSerial thread
    SerialWorker::StartWorker(&serialConnection);
}

//Parses a formatted string into sensor data objects
void RobotSensors::ParseData(QString data) {
    if (data.size() == 0) return;
}

double RobotSensors::GetIRValue(int index) {
    return irValues.at(index);
}

void RobotSensors::SetMotorValues(int left, int right) {
    emit SendData(QString("D:%1:%2").arg(left, right));
}
