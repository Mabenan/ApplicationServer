#include <application.h>
#include <consoleinput.h>

#include <Plugin.h>
#include <QCoreApplication>
#include <QDir>
#include <QLibraryInfo>
#include <QPluginLoader>
#include <QRegExp>
#include <QxHttpServer/QxHttpServer.h>
#include <WebInterface.h>

constexpr int inputWaitDetermin = 1000;
constexpr int serverPort = 8001;
Application::Application(QObject *parent)
    : ApplicationServerInterface(parent) {}
void Application::start() { this->initialize(); }

QList<QString> Application::GetCommands() { return this->commands.keys(); }
void Application::registerCommand(CommandInterface *commandInterface) {

  this->commands.insert(commandInterface->getName(), commandInterface);
}
void Application::registerWebInterface(WebInterface *webInterface) {

  this->webInterfaces.insert(webInterface->getName(), webInterface);
}
void Application::handleUserInput(const QString &command) {
  if (this->commands.contains(command)) {
    this->commands.value(command)->execute(this);
  } else if (command == QLatin1String("stop")) {
    inputThread.quit();
    if (inputThread.wait(inputWaitDetermin)) {
      inputThread.terminate();
      inputThread.wait();
    }
    Q_EMIT finished();
  } else {
    qWarning() << "Command: " << command << "not found";
  }
}

void Application::initialize() {

  // Init parameters to connect to database
  qx::QxSqlDatabase::getSingleton()->setDriverName(QStringLiteral("QSQLITE"));
  qx::QxSqlDatabase::getSingleton()->setDatabaseName(
      QStringLiteral("./test_qxorm.db"));
  qx::QxSqlDatabase::getSingleton()->setHostName(QStringLiteral("localhost"));
  qx::QxSqlDatabase::getSingleton()->setUserName(QStringLiteral("root"));
  qx::QxSqlDatabase::getSingleton()->setPassword(QLatin1String(""));
  qx::service::QxConnect::getSingleton()->setPort(serverPort);
  qx::service::QxConnect::getSingleton()->setSerializationType(
      qx::service::QxConnect::serialization_json);
  qx::dao::create_table<Plugin>();

  QDir pluginsDir = QDir(QCoreApplication::applicationDirPath());
  pluginsDir.cd(QStringLiteral("plugins"));
  pluginsDir.cd(QStringLiteral("server"));
  const auto entryList = pluginsDir.entryList(QDir::Files);
  for (const QString &fileName : entryList) {
    try {
      QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
      QObject *plugin = loader.instance();
      auto pluginInterface =
          qobject_cast<ApplicationServerPluginInterface *>(plugin);
      if (pluginInterface) {
        QString plugin_id = loader.fileName();
        auto *pluginObject = new Plugin();
        pluginObject->setId(plugin_id);
        QSqlError daoError = qx::dao::fetch_by_id(pluginObject);
        if (daoError.type() != QSqlError::NoError) {
          qx::dao::insert(pluginObject);
        }
        if (!pluginObject->getInstalled()) {
          pluginInterface->install(this);
          pluginObject->setInstalled(true);
          qx::dao::save(pluginObject);
        }
        pluginInterface->init(this);
      }
    } catch (std::exception *exc) {
      qDebug() << exc->what();
    }
  }
  this->httpServer.dispatch(
      QStringLiteral("GET"), QStringLiteral("/*"),
      [this](qx::QxHttpRequest &request, qx::QxHttpResponse &response) {
        QUrl url = request.url();
        Q_FOREACH (auto webIf, this->webInterfaces) {
          QRegExp exp = QRegExp(webIf->getRoute(this), Qt::CaseInsensitive);
          if (exp.exactMatch(url.path())) {
            webIf->execute(request, response, this);
          }
        }
      });
  this->httpServer.startServer();
  auto *input = new ConsoleInput();
  connect(this, &Application::startInput, input, &ConsoleInput::execute);
  connect(input, &ConsoleInput::input, this, &Application::handleUserInput);
  input->moveToThread(&inputThread);
  inputThread.start();
  Q_EMIT startInput();
}

void Application::onError(
    const QString &err,
    const qx::service::QxTransaction_ptr & /*transaction*/) {
  qDebug() << QDateTime::currentDateTime().toString(
                  QStringLiteral("dd.MM.yyyy hh:mm")) +
                  " : " + err;
}
void Application::registerAuthProvider(AuthProviderInterface *authProvider) {
  authProviders.append(authProvider);
}

bool Application::isUserAuthorized(const QString &user,
                                   const QString &authObject,
                                   const QMap<QString, QVariant> &params) {
  int globalAuthState = -1;
  for (AuthProviderInterface *authProvider : qAsConst(this->authProviders)) {
    int authState =
        authProvider->isUserAuthorized(user, authObject, params, this);
    if (authState > globalAuthState) {
      globalAuthState = authState;
    }
  }
  switch (globalAuthState) {
  case -1:
    return false;
  case 0:
    return true;
  case 1:
    return false;
  default:
    return false;
  }
}

QObject *Application::getValue(const QString &valueName) {
  if (!this->genericValues.contains(valueName)) {
    return nullptr;
  }
  return this->genericValues[valueName];
}

void Application::setValue(const QString &valueName, QObject *value) {
  if (!this->genericValues.contains(valueName)) {
    this->genericValues.insert(valueName, value);
  }
  this->genericValues[valueName] = value;
}

QList<QObject *> Application::getValues(const QString &valueName) {
  if (!this->genericListValues.contains(valueName)) {
    return QList<QObject *>();
  }
  return this->genericListValues[valueName];
}

void Application::addValue(const QString &valueName, QObject *value) {
  if (!this->genericListValues.contains(valueName)) {
    this->genericListValues.insert(valueName, QList<QObject *>());
  }
  this->genericListValues[valueName].append(value);
}
#include "moc_application.cpp"
