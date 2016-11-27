#ifndef TELEMETRYCONTROLLER_H
#define TELEMETRYCONTROLLER_H

#include <QUdpSocket>

#include <httpserver/httprequest.h>
#include <httpserver/httpresponse.h>
#include <httpserver/httprequesthandler.h>

using namespace stefanfrings;


class TelemetryController: public HttpRequestHandler
{
    Q_OBJECT
    Q_DISABLE_COPY(TelemetryController)
public:
    static TelemetryController *instance();
    ~TelemetryController();
    /** Generates the response */
    void service(HttpRequest& request, HttpResponse& response);

    void readTimeout(){}
private:
    TelemetryController();
    QUdpSocket _socket;
    QHostAddress _host;
    quint16 _port;
};

#endif // TELEMETRYCONTROLLER_H
