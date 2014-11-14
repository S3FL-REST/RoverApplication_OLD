#include <QCoreApplication>

#include <iostream>
#include <string>

#include "robotmain.h"

using namespace std;

const string SERIAL_PORT = "/dev/ttyACM0";

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    RobotMain robot(SERIAL_PORT);
    robot.StartRunLoop();

    return a.exec();
}
