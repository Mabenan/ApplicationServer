#include <QtTest>
#include <QCoreApplication>
#include <application.h>
#include <QList>
#include <QString>
#include "messagelogger.h"
// add necessary includes here

class FindsPlugins : public QObject
{
    Q_OBJECT

public:
     static FindsPlugins* currentTest;
public:
    FindsPlugins();
    ~FindsPlugins();
public:
    static void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);
private slots:
    void findsListPlugin();
};

FindsPlugins::FindsPlugins()
{
}

FindsPlugins::~FindsPlugins()
{

}

void FindsPlugins::myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    MessageLogger::instance()->log(msg);
}

void FindsPlugins::findsListPlugin()
{
    char * args;
    int argc = 0;
    qInstallMessageHandler(FindsPlugins::myMessageOutput); // Install the handler
    QCoreApplication a(argc, &args);
    Application* app = new Application(&a);
    app->start();
    app->handleUserInput("list");
    app->handleUserInput("stop");
    QVERIFY(MessageLogger::instance()->loggedMessages.contains("\"list\""));
}

QTEST_APPLESS_MAIN(FindsPlugins)

#include "tst_findsplugins.moc"
