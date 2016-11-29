#include <QJsonObject>
#include <QJsonDocument>

#include "manipcontroller.h"
#include "src/rovermanager.h"

ManipController::ManipController(QSettings *params)
    : _params(params)
{

}

void ManipController::service(HttpRequest &request, HttpResponse &response)
{
    response.setHeader("Content-Type", "application/json; charset=ISO-8859-1");
    QJsonObject responseJson;
    int responseStatus = 404;
    const QString start("start");
    if(request.getMethod() == "GET")
    {
        if(!request.getParameter("action").isEmpty())
        {
            if(0 == start.compare(QString(request.getParameter("action")),Qt::CaseInsensitive))
            {
                RoverManager::rover()->startManip();
                responseStatus = 200;
            }
            else
                responseStatus=403;
        } else
            responseStatus = 200;
    }
    if(request.getMethod() == "POST")
    {
        QJsonDocument requestDoc = QJsonDocument::fromJson(request.getBody());
        if(!requestDoc.isEmpty() && requestDoc.isObject())
        {
            QJsonObject requestJson = requestDoc.object();
            if(requestJson.contains("action"))
            {
                if(0 == start.compare(requestJson["action"].toString(),Qt::CaseInsensitive))
                {
                    RoverManager::rover()->startManip();
                    responseStatus = 200;
                }
                else
                    responseStatus=403;
            }
            else
                responseStatus=402;
        }
        else
        {
            qCritical()<<"ManipController: request JSON empty";
            responseStatus = 401;
        }
    }
    responseJson["state"]=RoverManager::toString(RoverManager::rover()->getManipState());
//    responseJson["stateId"]=QString::number((int)RoverManager::rover()->getManipState());
    QJsonDocument doc(responseJson);
    response.write(doc.toJson(),true);
    response.setStatus(responseStatus);
}
