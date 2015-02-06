#include <QCoreApplication>

#include <iostream>
#include <string>

#include "robotmain.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    RobotMain robot;
    robot.StartRunLoop();

    return a.exec();
}
