#include "robotmain.h"

RobotMain::RobotMain(string port) : robotData(), serialWorker(port), timer(this) {
    connect(this, SIGNAL(SendData(QString)), &serialWorker, SLOT(SendData(QString)));
    connect(&serialWorker, SIGNAL(ReceivedData(QString)), this, SLOT(RecievedData(QString)));

    SerialWorker::StartWorker(&serialWorker);

    timer.setInterval(5);
    connect(&timer, SIGNAL(timeout()), this, SLOT(RunLoop()));
}

void RobotMain::RecievedData(QString data) {
    if (!data.isEmpty()) cout << data.toStdString() << endl;
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

void RobotMain::RunLoop() {
    //robotData.Print(cout);
}

void RobotMain::SetMotorSpeeds(int lMotor, int rMotor) {
    cout << "Setting Motor Speeds L:" << lMotor << ", R:" << rMotor << endl;
    emit SendData(QString("D:%1:%2").arg(lMotor, rMotor));
}
