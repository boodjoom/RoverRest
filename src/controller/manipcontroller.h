#ifndef MANIPCONTROLLER_H
#define MANIPCONTROLLER_H

#include <httpserver/httprequest.h>
#include <httpserver/httpresponse.h>
#include <httpserver/httprequesthandler.h>

using namespace stefanfrings;

class ManipController: public HttpRequestHandler {
    Q_OBJECT
    Q_DISABLE_COPY(ManipController)
public:

    ManipController(QSettings *params);
    /** Generates the response */
    void service(HttpRequest& request, HttpResponse& response);

    void readTimeout(){}
private:
    QSettings* _params;
};

#endif // MANIPCONTROLLER_H
