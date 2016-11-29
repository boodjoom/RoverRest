#include <QJsonObject>
#include <QJsonDocument>

#include "manipcontroller.h"
#include "src/rovermanager.h"
#include "manipaction.h"

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
          const QString stop("stop");
          const QString base("base");
          const QString target("target");
          const QString home("home");
          const QString open("open");
          const QString close("close");
            if(0 == start.compare(QString(request.getParameter("action")),Qt::CaseInsensitive))
            {
                qDebug()<<"manip start request";
                RoverManager::rover()->startManip();
                responseStatus = 200;
            } else 
            if(0 == stop.compare(QString(request.getParameter("action")),Qt::CaseInsensitive))
            {
                RoverManager::rover()->execManip(ManipAction::Stop);
                responseStatus = 200;
            } else
            if(0 == base.compare(QString(request.getParameter("action")),Qt::CaseInsensitive))
            {
                RoverManager::rover()->execManip(ManipAction::Base);
                responseStatus = 200;
            } else
            if(0 == target.compare(QString(request.getParameter("action")),Qt::CaseInsensitive))
            {
                RoverManager::rover()->execManip(ManipAction::Target);
                responseStatus = 200;
            } else
            if(0 == home.compare(QString(request.getParameter("action")),Qt::CaseInsensitive))
            {
                RoverManager::rover()->execManip(ManipAction::Home);
                responseStatus = 200;
            } else
            if(0 == open.compare(QString(request.getParameter("action")),Qt::CaseInsensitive))
            {
                RoverManager::rover()->execManip(ManipAction::Open);
                responseStatus = 200;
            } else
            if(0 == close.compare(QString(request.getParameter("action")),Qt::CaseInsensitive))
            {
                RoverManager::rover()->execManip(ManipAction::Close);
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
    if(responseStatus<400)
    {
        responseJson["state"]=RoverManager::toString(RoverManager::rover()->getManipState());
    //    responseJson["stateId"]=QString::number((int)RoverManager::rover()->getManipState());
        QJsonDocument doc(responseJson);
        response.write(doc.toJson(),true);
    }
    response.setStatus(responseStatus);
}
