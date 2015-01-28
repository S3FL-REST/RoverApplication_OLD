#include "robotsensors.h"

const string RobotSensors::SERIAL_PORT("/dev/ttyACM0");

RobotSensors::RobotSensors() : irValues(NUM_IR_SENSORS, 0.0), serialConnection(SERIAL_PORT) {
    //Connect signals and slots for serial object
    connect(this, SIGNAL(SendData(QString)), &serialConnection, SLOT(SendData(QString)));
    connect(&serialConnection, SIGNAL(ReceivedData(QString)), this, SLOT(ParseString(QString)));

    //Start the robotSerial thread
    SerialWorker::StartWorker(&serialConnection);
}

//Parses a formatted string into sensor data objects
void RobotSensors::ParseString(QString data) {
    if (data.size() == 0) return;

    QStringList lines = data.split("\n");

    for (int i = 0; i < lines.length(); ++i) {
        if (lines.at(i).trimmed().size() == 0) continue;

        QStringList params = lines.at(i).split(":");

        QChar firstCharacter = params.at(0).at(0);
        int sensorNum = params.at(1).toInt();
        double value = params.at(2).toDouble();

        if (firstCharacter == QChar('i'))
            irValues.at(sensorNum) = value;
    }
}

double RobotSensors::GetIRValue(int index) {
    return irValues.at(index);
}
