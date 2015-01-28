#include "robotmain.h"

RobotMain::RobotMain() : robotData(), robotSensors(), networkClient(), networkData(), visionData(), timer(this) {
    //Connect signals and slots for network
    connect(&networkClient, SIGNAL(DataReceived(QByteArray)), &networkData, SLOT(ParseDataString(QByteArray)));
    connect(&networkClient, SIGNAL(ConnectionLost()), &networkData, SLOT(ResetToDefaults()));

    //Set the timer interval and connect the timer event to the robot run loop
    timer.setInterval(5);
    connect(&timer, SIGNAL(timeout()), this, SLOT(RunLoop()));

    currentAutonMode = TO_MINING;
}

void RobotMain::StartRunLoop() {
    timer.start();
    cout << "Starting Main Run Loop" << endl;
}

void RobotMain::StopRunLoop() {
    timer.stop();
    cout << "Stopping Main Run Loop" << endl;
}

void RobotMain::RunLoop() {
    if (networkData.GetCurrentRunMode() == TELEOP) {
        int joyL = networkData.GetJoystickLeft();
        int joyR = networkData.GetJoystickRight();

        robotData.SetMotorValues(joyL, joyR);
    } else if (networkData.GetCurrentRunMode() == FULL_AUTON || networkData.GetCurrentRunMode() == SAFE_AUTON) {
        if (networkData.GetCurrentRunMode() == SAFE_AUTON && !networkClient.IsConnected()) {
            robotData.SetMotorValues(0, 0);
            return;
        }

        if (visionData.IsInMiningArea() && currentAutonMode == TO_MINING)
            currentAutonMode = MINING;

        if (visionData.IsInHomeArea() && currentAutonMode == TO_HOME)
            currentAutonMode = HOME;

        if (currentAutonMode == TO_MINING) {
            if (visionData.IsInObstacleField()) {
                //CODE FOR NAVIAGTION


            } else {
                //Code for Going to Mining Area
				//This is now changed
            }
        } //Repeat for TO_HOME -> Make modifiers for single code base?
    }
}
