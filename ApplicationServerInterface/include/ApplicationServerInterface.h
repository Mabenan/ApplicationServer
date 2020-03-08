#ifndef APPLICATIONSERVERINTERFACE_H
#define APPLICATIONSERVERINTERFACE_H

#include <QObject>
#include <QString>
#include <ApplicationServerInterface_export.h>
class AuthProviderInterface;
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
    virtual void registerAuthProvider(AuthProviderInterface * authProvider) = 0;

    virtual bool isUserAuthorized(QString user, QString authObject, QMap<QString, QVariant> params) = 0;
    virtual QObject * getValue(QString valueName) = 0;
    virtual void setValue(QString valueName, QObject * value) = 0;
    virtual QList<QObject *> getValues(QString valueName) = 0;
    virtual void addValue(QString valueName, QObject * value) = 0;
};

#endif // APPLICATIONSERVERINTERFACE_H
