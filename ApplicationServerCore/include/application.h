#ifndef APPLICATION_H
#define APPLICATION_H

#include "ApplicationServerCore_global.h"
#include <ApplicationServerInterface>
#include <QDebug>
#include <QMap>
#include <QObject>
#include <QThread>
#include <QxHttpServer/QxHttpServer.h>
#include <QxService/QxThreadPool.h>

class APPLICATIONSERVERCORE_EXPORT Application
    : public ApplicationServerInterface {
  Q_OBJECT
private:
  QMap<QString, CommandInterface *> commands;
  QMap<QString, WebInterface *> webInterfaces;
  QList<AuthProviderInterface *> authProviders;
  qx::QxHttpServer httpServer;
  QMap<QString, QObject *> genericValues;
  QMap<QString, QList<QObject *>> genericListValues;
  qx::service::QxThreadPool_ptr
      m_pThreadPool; // Server thread pool to receive all requests
  QThread inputThread;

public:
  explicit Application(QObject *parent = nullptr);
  void handleUserInput(const QString &);
  void initialize();

Q_SIGNALS:
  void finished();
  void startInput();
public Q_SLOTS:
  void start();
  void onError(const QString &err,
               const qx::service::QxTransaction_ptr &transaction);

  // ApplicationServerInterface interface
public:
  QList<QString> GetCommands() override;
  void registerCommand(CommandInterface *commandInterface) override;
  void registerWebInterface(WebInterface *webInterface) override;

  void registerAuthProvider(AuthProviderInterface *authProvider) override;

  // ApplicationServerInterface interface
public:
  bool isUserAuthorized(QString user, QString authObject,
                        QMap<QString, QVariant> params) override;
  QObject *getValue(QString valueName) override;
  void setValue(QString valueName, QObject *value) override;
  QList<QObject *> getValues(QString valueName) override;
  void addValue(QString valueName, QObject *value) override;
};

#endif // APPLICATION_H
