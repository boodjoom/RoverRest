#ifndef ROVERMANAGER_H
#define ROVERMANAGER_H

#include <QSettings>
#include <QDateTime>
#include "rover.h"

class RoverManager
{
public:
    RoverManager();
    static Rover* rover();
};

#endif // ROVERMANAGER_H
