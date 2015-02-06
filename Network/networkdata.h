#ifndef NETWORKDATA_H
#define NETWORKDATA_H

#include <QObject>
#include "Protocols/rest_network.h"

using namespace std;


class NetworkData : public QObject
{
    Q_OBJECT

public:
    NetworkData();

    run_mode GetCurrentRunMode();
    int GetJoystickRight();
    int GetJoystickLeft();
    void SetMotors(int new_left, int new_right);

public slots:
     void ParseDataString(QByteArray);
     void ResetToDefaults();
     void Print(ostream&);

private:
    run_mode currentRunMode;
    int left;
    int right;

    int joystick_left;
    int joystick_right;

};

#endif // NETWORKDATA_H
