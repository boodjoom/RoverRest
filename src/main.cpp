#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <httpserver/httplistener.h>
#include <httpserver/staticfilecontroller.h>
#include <logging/filelogger.h>
#include "requestmapper.h"
#include "rovermanager.h"

using namespace stefanfrings;

/** Controller for static files */
StaticFileController* staticFileController;

/** Logger class */
FileLogger* logger;

/** Search the configuration file */
QString searchConfigFile(const QString& appName, const QString& confName = QString())
{
    QString binDir=QCoreApplication::applicationDirPath();
    QString fileName((confName.isEmpty()?appName:confName)+".ini");

    QStringList searchList;
    searchList.append(binDir);
    searchList.append(binDir+"/etc");
    searchList.append(binDir+"/../etc");
    searchList.append(binDir+"/../../etc"); // for development without shadow build
    searchList.append(binDir+"/../"+appName+"/etc"); // for development with shadow build
    searchList.append(binDir+"/../../"+appName+"/etc"); // for development with shadow build
    searchList.append(binDir+"/../../../"+appName+"/etc"); // for development with shadow build
    searchList.append(binDir+"/../../../../"+appName+"/etc"); // for development with shadow build
    searchList.append(binDir+"/../../../../../"+appName+"/etc"); // for development with shadow build
    searchList.append(QDir::rootPath()+"etc/opt");
    searchList.append(QDir::rootPath()+"etc");

    foreach (QString dir, searchList)
    {
        QFile file(dir+"/"+fileName);
        if (file.exists())
        {
            // found
            fileName=QDir(file.fileName()).canonicalPath();
            qDebug("Using config file %s",qPrintable(fileName));
            return fileName;
        }
    }

    // not found
    foreach (QString dir, searchList)
    {
        qWarning("%s/%s not found",qPrintable(dir),qPrintable(fileName));
    }
    qFatal("Cannot find config file %s",qPrintable(fileName));
    return 0;
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    app.setApplicationName("RoverRest");
    app.setOrganizationName("Shark Inc");

    // Find the configuration file
    QString configFileName=searchConfigFile(QCoreApplication::applicationName());

    // Configure logging into a file
//    QSettings* logSettings=new QSettings(configFileName,QSettings::IniFormat,&app);
//    logSettings->beginGroup("logging");
//    FileLogger* logger=new FileLogger(logSettings,10000,&app);
//    logger->installMsgHandler();

    // Configure static file controller
    QSettings* fileSettings=new QSettings(configFileName,QSettings::IniFormat,&app);
    fileSettings->beginGroup("docroot");
    staticFileController=new StaticFileController(fileSettings,&app);

    //Configure and start Rover
    QString roverConfigFile=searchConfigFile(QCoreApplication::applicationName(),"rover");
    QSettings roverSettings(roverConfigFile, QSettings::IniFormat);
    qDebug()<<"Call Rover init";
    RoverManager::instance()->init(roverSettings);
    qDebug()<<"Call Rover connect";
    RoverManager::instance()->connect();

    // Configure and start the TCP listener
    QSettings* listenerSettings=new QSettings(configFileName,QSettings::IniFormat,&app);
    listenerSettings->beginGroup("listener");
    new HttpListener(listenerSettings,new RequestMapper(&app),&app);

    qWarning("Application has started");

    int exitCode = app.exec();

    qWarning("Application has stopped with code %d",exitCode);

    return exitCode;
}
