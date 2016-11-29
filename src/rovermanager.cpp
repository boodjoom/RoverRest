#include "rovermanager.h"

RoverManager::RoverManager()
{

}

Rover *RoverManager::rover()
{
    static Rover* _instance = new Rover();
    return _instance;
}

QString RoverManager::toString(ManipState state)
{
    return Rover::toString(state);
}
