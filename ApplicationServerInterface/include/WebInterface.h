#ifndef WebInterface_H
#define WebInterface_H

#include <ApplicationServerInterface.h>

#include <ApplicationServerInterface_export.h>
#include <QObject>
#include <QtPlugin>
#include <QxHttpServer/QxHttpServer.h>
#include <QxOrm.h>
#include <QxServices.h>
#include <qstring.h>
class APPLICATION_SERVER_INTERFACE WebInterface : public QObject {
  Q_OBJECT
public:
  WebInterface(QObject *parent) : QObject(parent) {}
  ~WebInterface() = default;

  virtual QString getName() const = 0;
  virtual QString getRoute(ApplicationServerInterface *app) = 0;
  virtual void execute(qx::QxHttpRequest &request, qx::QxHttpResponse &response,
                       ApplicationServerInterface *app) = 0;
};
#endif // WebInterface_H
