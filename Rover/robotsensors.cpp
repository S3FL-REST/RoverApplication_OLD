#include "robotsensors.h"

const string RobotSensors::SERIAL_PORT("/dev/ttyACM0");

RobotSensors::RobotSensors() : irValues(NUM_IR_SENSORS, 0.0), serialConnection(SERIAL_PORT), currentLeft(0), currentRight(0) {
    //Connect signals and slots for serial object
    connect(this, SIGNAL(SendData(QString)), &serialConnection, SLOT(SendData(QString)));
    connect(&serialConnection, SIGNAL(ReceivedData(QString)), this, SLOT(ParseString(QString)));
}

//Parses a formatted string into sensor data objects
void RobotSensors::ParseString(QString data) {
    if (data.size() == 0) return;


    QStringList lines = data.split("\n");

    for (int i = 0; i < lines.length(); ++i) {
        if (lines.at(i).trimmed().size() == 0) continue;

        QStringList params = lines.at(i).split(":");

        if (params.length() >= 3) {
            QChar firstCharacter = params.at(0).at(0);
            int sensorNum = params.at(1).toInt();
            double value = params.at(2).toDouble();

            if (firstCharacter == QChar('i'))
                irValues.at(sensorNum) = value;
        }
    }
}

void RobotSensors::SetMotorValues(int left, int right) {
    if (currentLeft != left || currentRight != right) {
        emit SendData(QString("d:%1:%2\n\r").arg(left).arg(right));
        qDebug() << "Setting L:R to " << left << ":" << right;

        currentLeft = left;
        currentRight = right;
    }
}

double RobotSensors::GetIRValue(int index) {
    return irValues.at(index);
}

double RobotSensors::GetIRValue(IR_SENSORS index) {
    return irValues.at(static_cast<int>(index));
}
