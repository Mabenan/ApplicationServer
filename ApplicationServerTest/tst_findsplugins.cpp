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
    static FindsPlugins *currentTest;
    Application *app;
    QCoreApplication * a;

public:
    FindsPlugins();
    ~FindsPlugins();

public:
    static void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);
private slots:
    void initTestCase()
    {
        char *args;
        int argc = 0;
        qInstallMessageHandler(FindsPlugins::myMessageOutput); // Install the handler
        this->a = new QCoreApplication(argc, &args);
        this->app = new Application(a);
        this->app->start();
    }
    void findsListPlugin();

    void cleanupTestCase()
    {
        this->app->handleUserInput("stop");
        this->a->quit();
    }
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
    this->app->handleUserInput("list");
    QVERIFY(MessageLogger::instance()->loggedMessages.contains("\"list\""));
    QVERIFY(!MessageLogger::instance()->loggedMessages.contains("not found"));
}

QTEST_APPLESS_MAIN(FindsPlugins)

#include "tst_findsplugins.moc"
