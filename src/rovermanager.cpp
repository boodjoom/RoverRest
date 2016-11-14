#include "rovermanager.h"

RoverManager::RoverManager()
{

}

Rover *RoverManager::instance()
{
    static Rover* _instance = new Rover();
    return _instance;
}
