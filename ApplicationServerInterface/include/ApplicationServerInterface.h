#ifndef APPLICATIONSERVERINTERFACE_H
#define APPLICATIONSERVERINTERFACE_H

#include <ApplicationServerInterface_export.h>
#include <QObject>
#include <QString>
class AuthProviderInterface;
class CommandInterface;
class WebInterface;

class APPLICATION_SERVER_INTERFACE ApplicationServerInterface : public QObject {
  Q_OBJECT
public:
  ApplicationServerInterface(QObject *parent = nullptr) : QObject(parent) {}
  ~ApplicationServerInterface() override = default;
  virtual QList<QString> GetCommands() = 0;
  virtual void registerCommand(CommandInterface *commandInterface) = 0;
  virtual void registerWebInterface(WebInterface *webInterface) = 0;
  virtual void registerAuthProvider(AuthProviderInterface *authProvider) = 0;

  virtual bool isUserAuthorized(const QString &user,
                                const QString &authObject,
                                const QMap<QString, QVariant> &params) = 0;
  virtual QObject *getValue(const QString &valueName) = 0;
  virtual void setValue(const QString &valueName, QObject *value) = 0;
  virtual QList<QObject *> getValues(const QString &valueName) = 0;
  virtual void addValue(const QString &valueName, QObject *value) = 0;
};

#endif // APPLICATIONSERVERINTERFACE_H
