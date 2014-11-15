#include "serialconnection.h"

//Maximum Lost Count for Data Packets before Connection Close
const int SerialConnection::MAX_LOST_COUNT = 50;

SerialConnection::SerialConnection() : currentData(""), previousCommands(0), currentLostCount(0) {
    //Empty Constructor
}

//Opens Serial Connection and Sets Default Parameters for Connection
void SerialConnection::Connect(string port) {
    currentLostCount = 0;
    serial.Open(port);
    serial.SetBaudRate(SerialStreamBuf::BAUD_9600);
    serial.SetCharSize(SerialStreamBuf::CHAR_SIZE_8);

    qDebug() << "Opening port " << port.c_str();
}

//Closes Serial Connection
void SerialConnection::Close() {
    serial.Close();
}

//Returns boolean for connection opened or closed
bool SerialConnection::IsConnected() {
    return serial.IsOpen();
}

//Sends string data through serial
void SerialConnection::SendData(QString data) {
    if (IsConnected()) serial << data.toStdString().c_str();
}

//Gets all data in serial buffer and returns latest complete command
string SerialConnection::GetData() {
    if (!IsConnected())
        return "";

    char next_byte;

    if (serial.rdbuf()->in_avail() > 0) {
        currentLostCount = 0;

        while (serial.rdbuf()->in_avail() > 0) {
            serial.get(next_byte);
            currentData.push_back(next_byte);

            if (next_byte == ']') {
                serial.ignore(1);
                currentData.push_back('\n');

                previousCommands.push_back(currentData);
                currentData.clear();
            }
        }
    } else {
        if (currentLostCount > MAX_LOST_COUNT) Close();
        else currentLostCount++;
    }

    if (!previousCommands.empty()) {
        string dataToSend = previousCommands.back();
        previousCommands.clear();

        return dataToSend;
    } else {
        return "";
    }
}
