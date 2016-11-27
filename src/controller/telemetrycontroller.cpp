#include "telemetrycontroller.h"
#include <QJsonObject>
#include <QJsonDocument>

TelemetryController::TelemetryController()
   : _host("127.0.0.1")
   , _port(8888)
{

}

TelemetryController *TelemetryController::instance()
{
    static TelemetryController* _instance = new TelemetryController();
    return _instance;
}

TelemetryController::~TelemetryController()
{

}

void TelemetryController::service(HttpRequest &request, HttpResponse &response)
{
    response.setHeader("Content-Type", "application/json; charset=ISO-8859-1");
//    QJsonObject responseJson;
    int responseStatus = 400;
    if(request.getMethod() == "POST")
    {
        QJsonDocument requestDoc = QJsonDocument::fromJson(request.getBody());
        qDebug()<<"reques JSON isEmpty "<<requestDoc.isEmpty();
        if(requestDoc.isObject())
        {
            _socket.writeDatagram(requestDoc.toJson(),_host,_port);
            responseStatus=200;
        }
    }
//    QJsonDocument doc(responseJson);
//    response.write(doc.toJson(),true);
    response.setStatus(responseStatus);
}
