#ifndef ROVERMANAGER_H
#define ROVERMANAGER_H

#include <QSettings>
#include <QDateTime>
#include "rover.h"
//class Rover
//{
//public:
//    Rover(){}
//    void init(QSettings&){}
//    void connect(){}
//    void setRefSpeed(double speed, QDateTime timeout){}
//    void setRefYaw(double yaw){}
//    void startManip(){}
//};

class RoverManager
{
public:
    RoverManager();
    static Rover* rover();
};

#endif // ROVERMANAGER_H
