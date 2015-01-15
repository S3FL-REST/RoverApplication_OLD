#ifndef NETWORKDATA_H
#define NETWORKDATA_H

#include <QObject>
#include "Protocols/rest_network.pb.h"

using namespace rest_network;

class NetworkData : public QObject
{
    Q_OBJECT

public:
    NetworkData();

    run_mode GetCurrentRunMode();
    void SetMotors(int new_left, int new_right);

public slots:
     void ParseDataString(QByteArray);
     void ResetToDefaults();

private:
    run_mode currentRunMode;
    int left;
    int right;

    int joystick_left;
    int joystick_right;

};

#endif // NETWORKDATA_H
