#include <QJsonObject>
#include <QJsonDocument>
#include "vehiclecontroller.h"
#include "src/rovermanager.h"

VehicleController::VehicleController()
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
        qDebug()<<"vehicle GET";
        bool ok;
        if(!request.getParameter("speed").isEmpty())
        {
            double speed = request.getParameter("speed").toDouble(&ok);
            if(ok)
            {
                qDebug()<<"setSpeed "<<speed;
                RoverManager::instance()->setRefSpeed(speed);
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
                RoverManager::instance()->setRefYaw(yaw);
            }
            else
            {
                qDebug()<<"invalid param "<<request.getParameter("yaw");
            }
        }
//        response.write("<html><body>");
        response.write("RefSpeed = ");
        response.write(QString::number(RoverManager::instance()->getRefSpeed()).toLocal8Bit());
        response.write("\n");
        response.write("RefYaw = ");
        response.write(QString::number(RoverManager::instance()->getRefYaw()).toLocal8Bit());
//        response.write("</body></html>",true);
        response.write("\n",true);
    } else
    if(request.getMethod() == "POST")
    {
        qDebug()<<"vehicle POST request body: "<<request.getBody();
        QJsonDocument requestDoc = QJsonDocument::fromJson(request.getBody());
        qDebug()<<"reques JSON isEmpty "<<requestDoc.isEmpty();
        if(requestDoc.isObject())
        {
            QJsonObject requestJson = requestDoc.object();
            if(requestJson.contains("speed"))
            {
                bool ok;
                double speed = requestJson["speed"].toVariant().toDouble(&ok);
                if(ok)
                {
                    qDebug()<<"setSpeed "<<speed;
                    RoverManager::instance()->setRefSpeed(speed);
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
                    RoverManager::instance()->setRefYaw(yaw);
                }
                else
                {
                    qDebug()<<"invalid param "<<requestJson["yaw"].toString();
                }
            }
        }
    }
//    QJsonDocument doc(responseJson);
//    response.write(doc.toJson(),true);
    response.setStatus(200);

//    {
//        response.write("<html><body>");
//        response.write("Name = ");
//        response.write(request.getParameter("name"));
//        response.write("<br>City = ");
//        response.write(request.getParameter("city"));
//        response.write("</body></html>",true);
//    }
}
