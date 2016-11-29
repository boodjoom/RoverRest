#include <QJsonObject>
#include <QJsonDocument>

#include "statecontroller.h"
#include "src/rovermanager.h"

StateController::StateController(QSettings *params)
    : _params(params)
{

}

void StateController::service(HttpRequest &request, HttpResponse &response)
{
    response.setHeader("Content-Type", "application/json; charset=ISO-8859-1");
    QJsonObject responseJson;
    int responseStatus = 404;
    if(request.getMethod() == "GET")
    {
        responseStatus = 200;
        responseJson["speed"]=QString::number(RoverManager::rover()->getRefSpeed());
        responseJson["yaw"]=QString::number(RoverManager::rover()->getRefYaw());
        responseJson["travel"]=QString::number(RoverManager::rover()->getTravel());
        responseJson["state"]=RoverManager::toString(RoverManager::rover()->getManipState());
        responseJson["battery"]=QString::number(RoverManager::rover()->getBattery());
        QJsonDocument doc(responseJson);
        response.write(doc.toJson(),true);
    }
    response.setStatus(responseStatus);
}
