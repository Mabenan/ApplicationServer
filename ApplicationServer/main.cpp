#include <ApplicationServerCore>
#include <QCoreApplication>
#include <QTimer>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug() << QCoreApplication::applicationDirPath();
    Application* app = new Application(&a);
    // This will cause the application to exit when
    // the task signals finished.
    QObject::connect(app, SIGNAL(finished()), &a, SLOT(quit()));

    // This will run the task from the application event loop.
    QTimer::singleShot(0, app, SLOT(start()));
    return a.exec();
}
