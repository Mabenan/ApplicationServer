#include <application.h>
#include <consoleinput.h>

#include <QCoreApplication>
#include <QDir>
#include <QLibraryInfo>
#include <QPluginLoader>
#include <WebInterface.h>
Application::Application(QObject *parent) : ApplicationServerInterface(parent)
{
}
void Application::start()
{
    this->initialize();
}

QList<QString> Application::GetCommands()
{
    return this->commands.keys();
}
void Application::registerCommand(CommandInterface *commandInterface)
{

    this->commands.insert(commandInterface->getName(), commandInterface);
}
void Application::registerWebInterface(WebInterface *webInterface)
{

    this->webInterfaces.insert(webInterface->getName(), webInterface);
}
void Application::handleUserInput(QString command)
{
    if (this->commands.contains(command))
    {
        this->commands[command]->execute(this);
    }
    else if (command == "stop")
    {
        inputThread.quit();
        if (inputThread.wait(1000))
        {
            inputThread.terminate();
            inputThread.wait();
        }
        emit finished();
    }
    else
    {
        qWarning() << "Command: " << command << "not found";
    }
}

void Application::initialize()
{

    QDir pluginsDir = QDir(QCoreApplication::applicationDirPath());
    pluginsDir.cd("plugins");
    const auto entryList = pluginsDir.entryList(QDir::Files);
    for (const QString &fileName : entryList)
    {
        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = loader.instance();
        auto pluginInterface = qobject_cast<ApplicationServerPluginInterface *>(plugin);
        if (pluginInterface)
        {
            pluginInterface->init(this);
        }
    }
    this->httpServer = new QHttpServer(this);
    for (WebInterface *webIf : this->webInterfaces.values())
    {
        this->httpServer->route(webIf->getRoute(this),
                                [webIf, this](const QHttpServerRequest &request) {
                                    return webIf->execute(&request, this);
                                });
    }
    this->httpServer->listen(QHostAddress::Any, 8000);
    ConsoleInput *input = new ConsoleInput();
    connect(this, &Application::startInput, input, &ConsoleInput::execute);
    connect(input, &ConsoleInput::input, this, &Application::handleUserInput);
    input->moveToThread(&inputThread);
    inputThread.start();
    emit startInput();
}
#include "moc_application.cpp"