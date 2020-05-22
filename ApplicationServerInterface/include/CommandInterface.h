#ifndef COMMANDINTERFACE_H
#define COMMANDINTERFACE_H

#include <ApplicationServerInterface.h>

#include <ApplicationServerInterface_export.h>
#include <QObject>
#include <QtPlugin>
#include <qstring.h>

class APPLICATION_SERVER_INTERFACE CommandInterface : public QObject {
  Q_OBJECT
public:
  CommandInterface(QObject *parent) : QObject(parent) {}
  ~CommandInterface() = default;

  virtual QString getName() const = 0;
  virtual void execute(ApplicationServerInterface *app) = 0;
};
#endif // COMMANDINTERFACE_H
