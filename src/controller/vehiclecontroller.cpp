#include <QJsonObject>
#include <QJsonDocument>
#include "vehiclecontroller.h"
#include "src/rovermanager.h"

VehicleController::VehicleController(QSettings *params)
    : _params(params)
{

}

/*
 * {
 *      speed:1.0
 *      yaw:0.0
 *      timestamp:142331143
 *      timeout:2000
 * }
 *
 */

void VehicleController::service(HttpRequest &request, HttpResponse &response)
{
    response.setHeader("Content-Type", "application/json; charset=ISO-8859-1");
    QJsonObject responseJson;
    //parse raw params for get
    if(request.getMethod() == "GET")
    {
        unsigned long long timeout =0;
        qDebug()<<"vehicle GET";
        bool ok;
        if(!request.getParameter("speed").isEmpty())
        {
            double speed = request.getParameter("speed").toDouble(&ok);
            if(ok)
            {

                if(!request.getParameter("timeout").isEmpty())
                    timeout = request.getParameter("timeout").toULongLong(&ok);
                if(timeout==0)
                    timeout=_params->value("vehicleDefaultSpeedTimeout",0).toULongLong(&ok);
                qDebug()<<"setSpeed "<<speed<<" timeout "<<timeout;
                RoverManager::rover()->setRefSpeed(speed, timeout);
            }
            else
            {
                qDebug()<<"invalid param "<<request.getParameter("speed");
            }
        }
        if(!request.getParameter("yaw").isEmpty())
        {
            double yaw = request.getParameter("yaw").toDouble(&ok);
            if(ok)
            {
                qDebug()<<"setYaw "<<yaw;
                RoverManager::rover()->setRefYaw(yaw);
            }
            else
            {
                qDebug()<<"invalid param "<<request.getParameter("yaw");
            }
        }
//        response.write("<html><body>");
//        response.write("RefSpeed = ");
//        response.write(QString::number(RoverManager::rover()->getRefSpeed()).toLocal8Bit());
//        response.write("\n");
//        response.write("RefYaw = ");
//        response.write(QString::number(RoverManager::rover()->getRefYaw()).toLocal8Bit());
//        response.write("\n");
//        response.write("Timeout = ");
//        response.write(QString::number(timeout).toLocal8Bit());
////        response.write("</body></html>",true);
//        response.write("\n",true);
        responseJson["timeout"]=QString::number(timeout);
    } else
    if(request.getMethod() == "POST")
    {
        qDebug()<<"vehicle POST request body: "<<request.getBody();
        QJsonDocument requestDoc = QJsonDocument::fromJson(request.getBody());
        qDebug()<<"reques JSON isEmpty "<<requestDoc.isEmpty();
        if(requestDoc.isObject())
        {
            unsigned long long timeout =0;
            QJsonObject requestJson = requestDoc.object();
            if(requestJson.contains("speed"))
            {
                bool ok;
                double speed = requestJson["speed"].toVariant().toDouble(&ok);
                if(ok)
                {
                    if(requestJson.contains("timeout"))
                         timeout =  requestJson["timeout"].toVariant().toULongLong(&ok);
                    if(timeout==0)
                        timeout=_params->value("vehicleDefaultSpeedTimeout",0).toULongLong(&ok);
                    qDebug()<<"setSpeed "<<speed<<" timeout "<<timeout;
                    RoverManager::rover()->setRefSpeed(speed,timeout);
                }
                else
                {
                    qDebug()<<"invalid param "<<requestJson["speed"].toString();
                }
            }
            if(requestJson.contains("yaw"))
            {
                bool ok;
                double yaw = requestJson["yaw"].toVariant().toDouble(&ok);
                if(ok)
                {
                    qDebug()<<"setYaw "<<yaw;
                    RoverManager::rover()->setRefYaw(yaw);
                }
                else
                {
                    qDebug()<<"invalid param "<<requestJson["yaw"].toString();
                }
            }
        }
    }

    responseJson["speed"]=QString::number(RoverManager::rover()->getRefSpeed());
    responseJson["yaw"]=QString::number(RoverManager::rover()->getRefYaw());
    QJsonDocument doc(responseJson);
    response.write(doc.toJson(),true);
    response.setStatus(200);
}

void VehicleController::readTimeout()
{
    bool stopVehicleOnHttpTimeout=true;
    if(_params)
        stopVehicleOnHttpTimeout = _params->value("stopVehicleOnHttpTimeout",true).toBool();
    if(stopVehicleOnHttpTimeout)
        RoverManager::rover()->setRefSpeed(0);
}
