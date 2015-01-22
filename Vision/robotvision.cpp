#include "robotvision.h"

//Measurements in Meters

const double RobotVision::PI = 3.1415926;

const double RobotVision::LIMIT_OBSTACLE = 1.5;
const double RobotVision::LIMIT_MINING = 2.94;

RobotVision::RobotVision() : angle (0), distance (0), isTrackingCamera(false) {
    //Empty Constructor
}

void RobotVision::SetAngleAndDistance(double a, double d) {
    angle = a;
    distance = d;
}

double RobotVision::GetAngle() {
    return angle;
}

double RobotVision::GetDistance() {
    return distance;
}

double RobotVision::GetLinearDistance() {
    return distance * cos (angle * PI / 180.0);
}

bool RobotVision::IsTracking() {
    return false;
}

double RobotVision::GetLimitObstacle() {
    return LIMIT_OBSTACLE;
}

double RobotVision::GetLimitMining() {
    return LIMIT_MINING;
}

bool RobotVision::IsInObstacleField() {
    return (GetLinearDistance() < LIMIT_MINING && GetLinearDistance() > LIMIT_OBSTACLE);
}

bool RobotVision::IsInMiningArea() {
    return GetLinearDistance() > LIMIT_MINING;
}

bool RobotVision::IsInHomeArea() {
    return GetLinearDistance() < LIMIT_OBSTACLE;
}
