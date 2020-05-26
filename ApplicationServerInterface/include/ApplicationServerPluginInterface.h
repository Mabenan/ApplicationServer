#ifndef ApplicationServerPluginInterface_H
#define ApplicationServerPluginInterface_H

#include <ApplicationServerInterface>

#include <ApplicationServerInterface_export.h>
#include <QObject>
#include <QtPlugin>
#include <qstring.h>
#define ApplicationServerPluginInterface_iid "com.applicationserver.ApplicationServerPluginInterface/1.0"

class APPLICATION_SERVER_INTERFACE ApplicationServerPluginInterface
    : public QObject {
  Q_OBJECT
public:
  ApplicationServerPluginInterface(QObject *parent = nullptr)
      : QObject(parent) {}
  ~ApplicationServerPluginInterface() override = default;
  virtual void init(ApplicationServerInterface *app) = 0;
  virtual void install(ApplicationServerInterface *app) = 0;
};

Q_DECLARE_INTERFACE(ApplicationServerPluginInterface,
                    ApplicationServerPluginInterface_iid)
#endif // ApplicationServerPluginInterface_H
