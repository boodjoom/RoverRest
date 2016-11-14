#ifndef VEHICLECONTROLLER_H
#define VEHICLECONTROLLER_H

#include <httpserver/httprequest.h>
#include <httpserver/httpresponse.h>
#include <httpserver/httprequesthandler.h>

using namespace stefanfrings;

class VehicleController: public HttpRequestHandler {
    Q_OBJECT
    Q_DISABLE_COPY(VehicleController)
public:

    /** Constructor */
    VehicleController();

    /** Generates the response */
    void service(HttpRequest& request, HttpResponse& response);
};

#endif // VEHICLECONTROLLER_H
