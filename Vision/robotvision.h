#ifndef ROBOTVISION_H
#define ROBOTVISION_H

#include <cmath>

class RobotVision
{
public:
    RobotVision ();

     void SetAngleAndDistance (double, double);

     double GetAngle();
     double GetDistance();

     double GetLinearDistance();

     bool IsTracking();

     double GetLimitObstacle();
     double GetLimitMining();

     bool IsInObstacleField();

 private:
     double angle;
     double distance;

     double isTrackingCamera;

     static const double PI;

     static const double LIMIT_OBSTACLE;
     static const double LIMIT_MINING;
};

#endif // ROBOTVISION_H
