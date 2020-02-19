#ifndef APPLICATION_H
#define APPLICATION_H

#include "ApplicationServerCore_global.h"
#include <QObject>
#include <QThread>
#include <QMap>
#include <QDebug>
#include <ApplicationServerInterface>
#include <QHttpServer>


class APPLICATIONSERVERCORE_EXPORT Application : public ApplicationServerInterface
{
    Q_OBJECT
private:
    QMap<QString, CommandInterface*> commands;
    QMap<QString, WebInterface*> webInterfaces;
    QHttpServer * httpServer;
public:
    explicit Application(QObject *parent = nullptr);
    void handleUserInput(QString);
        void initialize();
        QThread inputThread;
signals:
    void finished();
    void startInput();
public slots:
    void start();

    // ApplicationServerInterface interface
public:
    QList<QString> GetCommands() override;
    void registerCommand(CommandInterface * commandInterface) override;
    void registerWebInterface(WebInterface * webInterface) override;
};

#endif // APPLICATION_H