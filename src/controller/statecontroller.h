#ifndef STATECONTROLLER_H
#define STATECONTROLLER_H

#include <httpserver/httprequest.h>
#include <httpserver/httpresponse.h>
#include <httpserver/httprequesthandler.h>

using namespace stefanfrings;

class StateController: public HttpRequestHandler {
    Q_OBJECT
    Q_DISABLE_COPY(StateController)
public:

    StateController(QSettings *params);
    /** Generates the response */
    void service(HttpRequest& request, HttpResponse& response);

    void readTimeout(){}
private:
    QSettings* _params;
};

#endif // STATECONTROLLER_H
