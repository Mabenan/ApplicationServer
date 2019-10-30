#include "application.h"
#include "consoleinput.h"

#include <QCoreApplication>
#include <QDir>
#include <QLibraryInfo>
#include <QPluginLoader>

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
void Application::handleUserInput(QString command)
{
    if (this->commands.contains(command)){
        this->commands[command]->execute(this);
    }else if (command == "stop")
    {
        inputThread.quit();
        emit finished();
    }else{
        qWarning() << "Command: " << command << "not found";
    }
}

void Application::initialize()
{

    QDir pluginsDir = QDir(QCoreApplication::applicationDirPath());
    pluginsDir.cd("plugins");
    const auto entryList = pluginsDir.entryList(QDir::Files);
    for (const QString &fileName : entryList) {
        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = loader.instance();
        auto iplugin = qobject_cast<CommandInterface*>(plugin);
        if(iplugin){
            this->commands.insert(iplugin->getName(), iplugin);
        }
    }
    ConsoleInput *input = new ConsoleInput();
    connect(this, &Application::startInput, input, &ConsoleInput::execute);
    connect(input, &ConsoleInput::input, this, &Application::handleUserInput);
    input->moveToThread(&inputThread);
    inputThread.start();
    emit startInput();
}
