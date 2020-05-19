#ifndef APPLICATION_H
#define APPLICATION_H

#include "ApplicationServerCore_global.h"
#include <QObject>
#include <QThread>
#include <QMap>
#include <QDebug>
#include <ApplicationServerInterface>
#include <QxHttpServer/QxHttpServer.h>
#include <QxService/QxThreadPool.h>

class APPLICATIONSERVERCORE_EXPORT Application : public ApplicationServerInterface
{
    Q_OBJECT
private:
    QMap<QString, CommandInterface*> commands;
    QMap<QString, WebInterface*> webInterfaces;
    QList<AuthProviderInterface *> authProviders;
	qx::QxHttpServer httpServer;
    QMap<QString, QObject *> genericValues;
    QMap<QString, QList<QObject *>> genericListValues;
    qx::service::QxThreadPool_ptr m_pThreadPool; // Server thread pool to receive all requests
public:
    explicit Application(QObject *parent = nullptr);
    void handleUserInput(QString);
        void initialize();
        QThread inputThread;

	virtual QList<QObject *> getValues(QString valueName) override;
	virtual void setValue(QString valueName, QObject * value) override;
	virtual void addValue(QString valueName, QObject * value) override;

signals:
    void finished();
    void startInput();
public slots:
    void start();
    void onError(const QString & err, qx::service::QxTransaction_ptr transaction);

    // ApplicationServerInterface interface
public:
    QList<QString> GetCommands() override;
    void registerCommand(CommandInterface * commandInterface) override;
    void registerWebInterface(WebInterface * webInterface) override;

	virtual bool isUserAuthorized(QString user, QString authObject,
			QMap<QString, QVariant> params) override;
	virtual void registerAuthProvider(AuthProviderInterface *authProvider) override;
	virtual QObject * getValue(QString valueName) override;
};

#endif // APPLICATION_H
