#ifndef ROBOTMAIN_H
#define ROBOTMAIN_H

#include <QObject>
#include <QString>
#include <QTimer>

#include "Computer/temperaturemonitor.h"

#include "Rover/serialworker.h"
#include "Rover/robotdata.h"
#include "Rover/robotsensors.h"

#include "Network/networkclient.h"
#include "Network/networkdata.h"

#include "Vision/camera.h"
#include "Vision/robotvision.h"

#include <iostream>
#include <cassert>

using namespace std;

enum AUTONOMY_MODES {
    TO_MINING,
    MINING,
    TO_HOME,
    HOME,
    END
};

class RobotMain : public QObject
{
    Q_OBJECT
public:
    RobotMain();

    void StartRunLoop();
    void StopRunLoop();

private:
    RobotData robotData;
    RobotSensors robotSensors;

    NetworkClient networkClient;
    NetworkData networkData;

    RobotVision visionData;

    QTimer timer;
    QTimer visionTimer;
    QTimer slowTimer;

    Camera camera_front_right;

    AUTONOMY_MODES currentAutonMode;

    void SetMotorSpeeds(int, int);

signals:
    void SendData(QString);

private slots:
    void RunLoop();
    void VisionLoop();
    void SlowLoop();
};

#endif // ROBOTMAIN_H
