#ifndef WebInterface_H
#define WebInterface_H

#include <ApplicationServerInterface.h>

#include <QObject>
#include <QtPlugin>
#include <qstring.h>
#include <QHttpServer>
#include <ApplicationServerInterface_export.h>

class APPLICATION_SERVER_INTERFACE WebInterface : public QObject
{
    Q_OBJECT
public:
    WebInterface(QObject* parent): QObject(parent){

    }
    virtual~WebInterface(){}

    virtual QString getName() const = 0;
    virtual QString getRoute(ApplicationServerInterface * app) = 0;
    virtual QHttpServerResponse execute(const QHttpServerRequest * request, ApplicationServerInterface * app) = 0;
};
#endif // WebInterface_H
