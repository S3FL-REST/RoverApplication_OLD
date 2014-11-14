#include "robotdata.h"

//Temperature Filepath: /sys/class/thermal/thermal_zone0/temp

RobotData::RobotData() : encoderValues(NUM_ENCODERS), irValues(NUM_IR_SENSORS), imuValues(NUM_IMU_DATA) {
    //Empty Constructor
}

void RobotData::ParseString(QString data) {
    if (data.size() == 0) return;

    istringstream inputStream(data.toStdString());

    string currentLine;
    getline(inputStream, currentLine);

    try {
        while (!inputStream.fail() && currentLine != "]") {
            InterpretDataType(currentLine);
            getline(inputStream, currentLine);
        }
    } catch (...) {
        qDebug() << "ERROR!!!";
        qDebug() << currentLine.c_str();
        qDebug() << data << endl;
    }
}

void RobotData::ParseSingleData(string currentLine, vector<int>& array) {
    int sensorNum = currentLine.at(1) - '0' - 1;
    int value = atoi(currentLine.substr(3).c_str());
    array.at(sensorNum) = value;
}

void RobotData::InterpretDataType(string currentLine) {
    if (currentLine.empty())
        return;

    char inputType = currentLine.at(0);
    if (inputType == 'E')
        ParseSingleData(currentLine, encoderValues);
    else if (inputType == 'I')
        ParseSingleData(currentLine, irValues);
    else if (inputType == 'A') {
        size_t pos = 0;
        string token;
        string delimiter = ":";

        string s = currentLine.substr(2, currentLine.size() - 2).append(":");

        int i = 0;

        while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            imuValues.at(i) = atoi(token.c_str());
            s.erase(0, pos + delimiter.length());
            i++;
        }
    }
}

void RobotData::Print(ostream& out) {
    out << "E - ";
    for (size_t i = 0; i < encoderValues.size(); i++) out << encoderValues.at(i) << " ";
    out << endl;

    out << "I - ";
    for (size_t i = 0; i < irValues.size(); i++) out << irValues.at(i) << " ";
    out << endl;

    out << "A - ";
    for (size_t i = 0; i < imuValues.size(); i++) out << imuValues.at(i) << " ";
    out << endl;
}
