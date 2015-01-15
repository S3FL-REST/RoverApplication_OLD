#include "networkdata.h"

#include <QDebug>

NetworkData::NetworkData() : currentRunMode(NetworkData::NONE) {
    //Empty Constructor
}

NetworkData::RunMode NetworkData::GetCurrentRunMode() {
    return currentRunMode;
}

void NetworkData::ParseDataString(QByteArray data) {
    ControlNetworkData controlData;
    controlData.ParseFromArray(data, data.length());

    qDebug() << controlData.left() << ", " << controlData.right() << ", " << controlData.mode();
}
