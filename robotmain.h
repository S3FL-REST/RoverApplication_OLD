#ifndef ROBOTMAIN_H
#define ROBOTMAIN_H

#include <QObject>
#include <QString>
#include <QTimer>

#include <string>

#include "Rover/serialworker.h"
#include "Rover/robotdata.h"

#include "Network/networkclient.h"
#include "Network/networkdata.h"

#include <iostream>

using namespace std;

class RobotMain : public QObject
{
    Q_OBJECT
public:
    RobotMain(string);

    void StartRunLoop();
    void StopRunLoop();

private:
    RobotData robotData;
    SerialWorker robotSerial;

    NetworkClient networkClient;
    NetworkData networkData;

    QTimer timer;

    void SetMotorSpeeds(int, int);


signals:
    void SendData(QString);

private slots:
    void RecievedData(QString);
    void RunLoop();
};

#endif // ROBOTMAIN_H
