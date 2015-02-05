#include "robotmain.h"

RobotMain::RobotMain() : robotData(), robotSensors(), networkClient(), networkData(), visionData(), timer(this) {
    //Connect signals and slots for network
    connect(&networkClient, SIGNAL(DataReceived(QByteArray)), &networkData, SLOT(ParseDataString(QByteArray)));
    connect(&networkClient, SIGNAL(ConnectionLost()), &networkData, SLOT(ResetToDefaults()));

    //Set the timer interval and connect the timer event to the robot run loop
    timer.setInterval(5);
    connect(&timer, SIGNAL(timeout()), this, SLOT(RunLoop()));

    //Set Current Auton Mode
    currentAutonMode = TO_MINING;

    //TODO: NEED A VISION LOOP
}

void RobotMain::StartRunLoop() {
    timer.start();
    cout << "Starting Main Run Loop" << endl;
}

void RobotMain::StopRunLoop() {
    timer.stop();
    cout << "Stopping Main Run Loop" << endl;
}

//Thresholds for Target Position Difference and Angle Difference
static const double TARGET_THRESHOLD = 1.0;
static const double MAX_ANGLE = 30.0;

//Thresholds for Max Motor Speed and Max Turning Difference
static const int MAX_SPEED = 200;
static const int MAX_TURN_DIFFERENCE = 50;

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

        //Current Target Position from Horizontal
        double targetPosHorizontal = 0.0;

        //New Motor Speeds -> To be set later in code
        int lMotor = MAX_SPEED;
        int rMotor = MAX_SPEED;

        if (currentAutonMode == TO_MINING || currentAutonMode == TO_HOME) {
            double irLeft, irRight;

            if (currentAutonMode == TO_MINING) {
                irLeft = robotSensors.GetIRValue(IR_FRONT_LEFT);
                irRight = robotSensors.GetIRValue(IR_FRONT_RIGHT);
            } else {
                irLeft = robotSensors.GetIRValue(IR_BACK_RIGHT);
                irRight = robotSensors.GetIRValue(IR_BACK_LEFT);
            }

            double robotTurnRatio = abs((visionData.GetRobotAngle() - MAX_ANGLE) / MAX_ANGLE);

            double horizontalDifference = visionData.GetHorizontalDistance() - targetPosHorizontal;

            if (horizontalDifference > TARGET_THRESHOLD) {
                if (robotTurnRatio <= 1.0)
                    rMotor -= robotTurnRatio * MAX_TURN_DIFFERENCE;
            }
            else if (horizontalDifference < -TARGET_THRESHOLD) {
                if (robotTurnRatio <= 1.0)
                    lMotor -= robotTurnRatio * MAX_TURN_DIFFERENCE;
            }

            //Collision Avoidance

            if (irLeft > robotSensors.CRATER_LIMIT && irLeft < robotSensors.ROCK_LIMIT)
                rMotor = -rMotor;

            if (irRight > robotSensors.CRATER_LIMIT && irRight < robotSensors.ROCK_LIMIT)
                lMotor = -lMotor;
        }

        if (currentAutonMode == TO_MINING)
            robotData.SetMotorValues(lMotor, rMotor);
        else if (currentAutonMode == TO_HOME)
            robotData.SetMotorValues(-rMotor, -lMotor);
        else {
            qDebug() << "DID NOT SET MOTOR VALUES -> UNKNOWN STATE";
            robotData.SetMotorValues(0, 0);
        }
    }
}
