#ifndef APPLICATIONSERVERINTERFACE_H
#define APPLICATIONSERVERINTERFACE_H

#include <QObject>
#include <QString>
#include <ApplicationServerInterface_export.h>
class CommandInterface;
class WebInterface;

class APPLICATION_SERVER_INTERFACE ApplicationServerInterface : public QObject
{
    Q_OBJECT
public:
    ApplicationServerInterface(QObject* parent): QObject(parent){

    }
    virtual~ApplicationServerInterface(){}
    virtual QList<QString> GetCommands() = 0;
    virtual void registerCommand(CommandInterface * commandInterface)= 0;
    virtual void registerWebInterface(WebInterface * webInterface)= 0;

};

#endif // APPLICATIONSERVERINTERFACE_H
