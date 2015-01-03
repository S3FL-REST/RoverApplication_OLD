#include <QCoreApplication>

#include <iostream>
#include <string>

#include "robotmain.h"

using namespace std;

const string SERIAL_PORT = "/dev/ttyACM0";

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    GOOGLE_PROTOBUF_VERIFY_VERSION;

    RobotMain robot(SERIAL_PORT);
    robot.StartRunLoop();

    return a.exec();
}
