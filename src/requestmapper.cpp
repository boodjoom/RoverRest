/**
  @file
  @author Stefan Frings
*/

#include <QCoreApplication>
#include <logging/filelogger.h>
#include <httpserver/staticfilecontroller.h>
#include "requestmapper.h"
#include "controller/vehiclecontroller.h"
#include "controller/telemetrycontroller.h"
#include "controller/manipcontroller.h"
#include "controller/statecontroller.h"

/** Redirects log messages to a file */
extern FileLogger* logger;

/** Controller for static files */
extern StaticFileController* staticFileController;

RequestMapper::RequestMapper(QSettings *params, QObject* parent)
    :HttpRequestHandler(parent)
    , _params(params)
{
    qDebug("RequestMapper: created");
}


RequestMapper::~RequestMapper()
{
    qDebug("RequestMapper: deleted");
}


void RequestMapper::service(HttpRequest& request, HttpResponse& response)
{
    QByteArray path=request.getPath();
    qDebug("RequestMapper: path=%s",path.data());

    // For the following pathes, each request gets its own new instance of the related controller.

    if (path.startsWith("/vehicle"))
    {
        qInfo("vehicle service");
        VehicleController(_params).service(request,response);
    } else

    if (path.startsWith("/manip"))
    {
        qInfo("manip service");
        ManipController(_params).service(request,response);
    } else

    if (path.startsWith("/state"))
    {
        qInfo("state service");
        StateController(_params).service(request,response);
    } else

    if (path.startsWith("/telemetry"))
    {
        qInfo("telemetry service");
        TelemetryController::instance()->service(request, response);
    }

    // All other pathes are mapped to the static file controller.
    // In this case, a single instance is used for multiple requests.
    else
    {
        staticFileController->service(request, response);
    }

    qDebug("RequestMapper: finished request");

    // Clear the log buffer
    if (logger)
    {
       logger->clear();
    }
}

void RequestMapper::readTimeout()
{
    VehicleController(_params).readTimeout();
}
