#ifndef NETWORKDATA_H
#define NETWORKDATA_H

#include <QObject>

class NetworkData : public QObject
{
    Q_OBJECT

public:
    enum RunMode {TELEOP, AUTON, AUTON_SAFE, NONE};

    NetworkData();

    RunMode GetCurrentRunMode();

private:
    RunMode currentRunMode;
};

#endif // NETWORKDATA_H
