#ifndef AUTHPRODVIDERINTERFACE_H
#define AUTHPRODVIDERINTERFACE_H

#include <ApplicationServerInterface.h>

#include <ApplicationServerInterface_export.h>
#include <QObject>
#include <qstring.h>

class APPLICATION_SERVER_INTERFACE AuthProviderInterface : public QObject {
  Q_OBJECT
public:
  AuthProviderInterface(QObject *parent = nullptr) : QObject(parent) {}
  ~AuthProviderInterface() = default;

  virtual QString getName() const = 0;
  virtual int isUserAuthorized(const QString &user, QString authObject,
                               QMap<QString, QVariant> params,
                               ApplicationServerInterface *app) = 0;
};
#endif // AUTHPRODVIDERINTERFACE_H
