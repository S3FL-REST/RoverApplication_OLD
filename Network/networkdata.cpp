#include "networkdata.h"

#include <QDebug>

NetworkData::NetworkData() : currentRunMode(STOP), left(0), right(0), joystick_left(0), joystick_right(0) {
    //Empty Constructor
}

run_mode NetworkData::GetCurrentRunMode() {
    return currentRunMode;
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
    ControlNetworkData controlData;
    controlData.ParseFromArray(data, data.length());

    if (controlData.has_mode())
        currentRunMode = controlData.mode();

    if (controlData.has_left())
        joystick_left = controlData.left();

    if (controlData.has_right())
        joystick_right = controlData.right();
}

void NetworkData::ResetToDefaults() {
    currentRunMode = STOP;
    left = 0;
    right = 0;
    joystick_left = 0;
    joystick_right = 0;
}

void NetworkData::Print(ostream &out) {
    out << "Mode: " << currentRunMode << endl;
    out << "Left: " << left << ", Right: " << right << endl;
    out << "Joy Left: " << joystick_left << ", Joy Right: " << joystick_right << endl;
}
