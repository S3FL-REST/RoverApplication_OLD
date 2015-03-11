#ifndef REST_NETWORK_H
#define REST_NETWORK_H

#include <QString>
#include <QStringList>

#include <QByteArray>

#include <QImage>
#include <QBuffer>
#include <QDataStream>

enum run_mode {
  STOP = 0,
  TELEOP = 1,
  SAFE_AUTON = 2,
  FULL_AUTON = 3
};

class rest_network
{
public:
    rest_network();

    void SetLeftJoystick(int);
    void SetRightJoystick(int);
    void SetRunMode(run_mode);
    void SetImage(QImage);

    int GetLeftJoystick();
    int GetRightJoystick();
    run_mode GetRunMode();
    QImage GetImage();

    QByteArray ToByteArray();
    bool ParseString(QString);


private:
    int left_joystick;
    int right_joystick;
    run_mode current_mode;
    QImage image;

    bool new_picture;
};

#endif // REST_NETWORK_H
