#include "robotmain.h"

RobotMain::RobotMain(string serial_port) : robotData(), robotSerial(serial_port), networkClient(), networkData(), timer(this) {

    //Connect signals and slots for serial object
    connect(this, SIGNAL(SendData(QString)), &robotSerial, SLOT(SendData(QString)));
    connect(&robotSerial, SIGNAL(ReceivedData(QString)), this, SLOT(RecievedData(QString)));

    //Connect signals and slots for network
    connect(&networkClient, SIGNAL(DataReceived(QByteArray)), &networkData, SLOT(ParseDataString(QByteArray)));
    connect(&networkClient, SIGNAL(ConnectionLost()), &networkData, SLOT(ResetToDefaults()));

    //Start the robotSerial thread
    SerialWorker::StartWorker(&robotSerial);

    //Set the timer interval and connect the timer event to the robot run loop
    timer.setInterval(5);
    connect(&timer, SIGNAL(timeout()), this, SLOT(RunLoop()));
}

void RobotMain::RecievedData(QString data) {
    robotData.ParseString(data);
}

void RobotMain::StartRunLoop() {
    timer.start();
    cout << "Starting Main Run Loop" << endl;
}

void RobotMain::StopRunLoop() {
    timer.stop();
    cout << "Stopping Main Run Loop" << endl;
}

int j = 0;

void RobotMain::RunLoop() {
    //robotData.Print(cout);

    if (networkData.GetCurrentRunMode() == STOP) {
        cout << "STOP " << j << endl;
        j++;
    }
}

void RobotMain::SetMotorSpeeds(int lMotor, int rMotor) {
    cout << "Setting Motor Speeds L:" << lMotor << ", R:" << rMotor << endl;
    emit SendData(QString("D:%1:%2").arg(lMotor, rMotor));
}
