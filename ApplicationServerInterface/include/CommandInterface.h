#ifndef COMMANDINTERFACE_H
#define COMMANDINTERFACE_H

#include <ApplicationServerInterface.h>

#include <QObject>
#include <QtPlugin>
#include <qstring.h>
#include <ApplicationServerInterface_export.h>

class APPLICATION_SERVER_INTERFACE CommandInterface : public QObject
{
    Q_OBJECT
public:
    CommandInterface(QObject* parent): QObject(parent){

    }
    virtual~CommandInterface(){}

    virtual QString getName() const = 0;
    virtual void execute(ApplicationServerInterface * app) = 0;
};
#endif // COMMANDINTERFACE_H
