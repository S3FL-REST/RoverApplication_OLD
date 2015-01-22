#include <QCoreApplication>

#include <iostream>
#include <string>

#include "robotmain.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    GOOGLE_PROTOBUF_VERIFY_VERSION;

    cout << "TEST WITH SERIAL AGAIN!!!" << endl << endl;
    cout << "Switch to ProtoBuf or similar for Serial Connections" << endl << endl;

    RobotMain robot;
    robot.StartRunLoop();

    return a.exec();
}
