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
    if(request.getMethod() == "POST")
    {
        QJsonDocument requestDoc = QJsonDocument::fromJson(request.getBody());
        if(!requestDoc.isEmpty() && requestDoc.isObject())
        {
            QJsonObject requestJson = requestDoc.object();
            if(requestJson.contains("action"))
            {
                const QString start("start");
                if(0 == start.compare(requestJson["action"].toString(),Qt::CaseInsensitive))
                {
                    //!start manip
                }
            }
        }
        else
        {
            qCritical()<<"ManipController: request JSON empty";
        }
    }
}
