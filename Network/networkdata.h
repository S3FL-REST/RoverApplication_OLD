#ifndef NETWORKDATA_H
#define NETWORKDATA_H

#include <QObject>
#include "Protocols/rest_network.pb.h"

using namespace rest_network;

class NetworkData : public QObject
{
    Q_OBJECT

public:
    enum RunMode {TELEOP, AUTON, AUTON_SAFE, NONE};

    NetworkData();

    RunMode GetCurrentRunMode();

public slots:
     void ParseDataString(QByteArray);

private:
    RunMode currentRunMode;
};

#endif // NETWORKDATA_H
