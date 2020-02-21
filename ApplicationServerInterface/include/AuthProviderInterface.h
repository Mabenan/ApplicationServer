#ifndef AUTHPRODVIDERINTERFACE_H
#define AUTHPRODVIDERINTERFACE_H

#include <ApplicationServerInterface.h>

#include <QObject>
#include <QtPlugin>
#include <qstring.h>
#include <ApplicationServerInterface_export.h>

class APPLICATION_SERVER_INTERFACE AuthProviderInterface : public QObject
{
    Q_OBJECT
public:
	AuthProviderInterface(QObject* parent): QObject(parent){

    }
    virtual~AuthProviderInterface(){}

    virtual QString getName() const = 0;
    virtual int isUserAuthorized(QString user, QString authObject, QMap<QString, QVariant> params, ApplicationServerInterface * app) = 0;
};
#endif // AUTHPRODVIDERINTERFACE_H
