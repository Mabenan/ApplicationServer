#ifndef ApplicationServerPluginInterface_H
#define ApplicationServerPluginInterface_H

#include <ApplicationServerInterface>

#include <QObject>
#include <QtPlugin>
#include <qstring.h>
#include <ApplicationServerInterface_export.h>
#define ApplicationServerPluginInterface_iid "com.applicationserver.ApplicationServerPluginInterface/1.0"

class APPLICATION_SERVER_INTERFACE ApplicationServerPluginInterface : public QObject
{
    Q_OBJECT
public:
    ApplicationServerPluginInterface(QObject* parent): QObject(parent){

    }
    virtual~ApplicationServerPluginInterface(){}
    virtual void init(ApplicationServerInterface * app) = 0;
    virtual void install(ApplicationServerInterface * app) = 0;
};

Q_DECLARE_INTERFACE(ApplicationServerPluginInterface, ApplicationServerPluginInterface_iid)
#endif // ApplicationServerPluginInterface_H
