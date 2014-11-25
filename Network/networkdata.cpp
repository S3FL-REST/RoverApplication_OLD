#include "networkdata.h"

NetworkData::NetworkData() : currentRunMode(NetworkData::NONE) {
    //Empty Constructor
}

NetworkData::RunMode NetworkData::GetCurrentRunMode() {
    return currentRunMode;
}

void NetworkData::ParseDataString(QString) {

}
