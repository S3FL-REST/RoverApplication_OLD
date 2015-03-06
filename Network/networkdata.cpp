#include "networkdata.h"

#include <QDebug>

NetworkData::NetworkData() : currentRunMode(STOP), left(0), right(0), joystick_left(0), joystick_right(0) {
    //Empty Constructor
}

run_mode NetworkData::GetCurrentRunMode() {
    return currentRunMode;
}

int NetworkData::GetJoystickLeft() {
    return joystick_left;
}

int NetworkData::GetJoystickRight() {
    return joystick_right;
}

void NetworkData::SetMotors(int new_left, int new_right) {
    const int RANGE_LIMIT = 255;

    if (new_left >= -RANGE_LIMIT && new_left <= RANGE_LIMIT)
        left = new_left;
    else
        qDebug() << "Left Range out of Bounds: " << new_left;

    if (new_right >= -RANGE_LIMIT && new_right <= RANGE_LIMIT)
        right = new_right;
    else
        qDebug() << "Right Range out of Bounds: " << new_right;
}

void NetworkData::ParseDataString(QByteArray data) {
    rest_network controlData;

    if (controlData.ParseString(QString(data))) {
        currentRunMode = controlData.GetRunMode();
        joystick_left = controlData.GetLeftJoystick();
        joystick_right = controlData.GetRightJoystick();

        //qDebug() << joystick_left << ", " << joystick_right << ", " << currentRunMode;
    }
}

void NetworkData::ResetToDefaults() {
    if (currentRunMode != FULL_AUTON) {
        currentRunMode = STOP;
        left = 0;
        right = 0;
    }


    joystick_left = 0;
    joystick_right = 0;

}

void NetworkData::Print(ostream &out) {
    out << "Mode: " << currentRunMode << endl;
    out << "Left: " << left << ", Right: " << right << endl;
    out << "Joy Left: " << joystick_left << ", Joy Right: " << joystick_right << endl;
}
