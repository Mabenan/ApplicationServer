#ifndef APPLICATION_H
#define APPLICATION_H

#include <CommandInterface.h>
#include <QObject>
#include <QThread>
#include <QMap>
#include <QDebug>
#include <ApplicationServerInterface.h>


class Application : public ApplicationServerInterface
{
    Q_OBJECT
private:
    QMap<QString, CommandInterface*> commands;
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
};

#endif // APPLICATION_H
