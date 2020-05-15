#include <application.h>
#include <consoleinput.h>

#include <QCoreApplication>
#include <QDir>
#include <QLibraryInfo>
#include <QPluginLoader>
#include <WebInterface.h>
#include <QxOrm.h>
#include <Plugin.h>
#include <QxConnect.h>
Application::Application(QObject *parent) :
		ApplicationServerInterface(parent) {
	this->httpServer = new QHttpServer(this);
}
void Application::start() {
	this->initialize();
}

QList<QString> Application::GetCommands() {
	return this->commands.keys();
}
void Application::registerCommand(CommandInterface *commandInterface) {

	this->commands.insert(commandInterface->getName(), commandInterface);
}
void Application::registerWebInterface(WebInterface *webInterface) {

	this->webInterfaces.insert(webInterface->getName(), webInterface);
}
void Application::handleUserInput(QString command) {
	if (this->commands.contains(command)) {
		this->commands[command]->execute(this);
	} else if (command == "stop") {
		inputThread.quit();
		if (inputThread.wait(1000)) {
			inputThread.terminate();
			inputThread.wait();
		}
		emit finished();
	} else {
		qWarning() << "Command: " << command << "not found";
	}
}

void Application::initialize() {

	// Init parameters to connect to database
	qx::QxSqlDatabase::getSingleton()->setDriverName("QSQLITE");
	qx::QxSqlDatabase::getSingleton()->setDatabaseName("./test_qxorm.db");
	qx::QxSqlDatabase::getSingleton()->setHostName("localhost");
	qx::QxSqlDatabase::getSingleton()->setUserName("root");
	qx::QxSqlDatabase::getSingleton()->setPassword("");
	qx::service::QxConnect::getSingleton()->setPort(8001);
	qx::service::QxConnect::getSingleton()->setSerializationType(qx::service::QxConnect::serialization_json);
	qx::dao::create_table<Plugin>();

	QDir pluginsDir = QDir(QCoreApplication::applicationDirPath());
	pluginsDir.cd("plugins");
	pluginsDir.cd("server");
	const auto entryList = pluginsDir.entryList(QDir::Files);
	for (const QString &fileName : entryList) {
		try {
			QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
			QObject *plugin = loader.instance();
			auto pluginInterface = qobject_cast<
					ApplicationServerPluginInterface*>(plugin);
			if (pluginInterface) {
				QString plugin_id = loader.fileName();
				Plugin *pluginObject = new Plugin();
				pluginObject->id = plugin_id;
				QSqlError daoError = qx::dao::fetch_by_id(pluginObject);
				if (daoError.type() != QSqlError::NoError) {
					qx::dao::insert(pluginObject);
				}
				if (!pluginObject->installed) {
					pluginInterface->install(this);
					pluginObject->installed = true;
					qx::dao::save(pluginObject);
				}
				pluginInterface->init(this);
			}
		} catch (std::exception *exc) {
			qDebug() << exc->what();
		}
	}
	for (WebInterface *webIf : this->webInterfaces.values()) {
		this->httpServer->route(webIf->getRoute(this),
				[webIf, this](const QHttpServerRequest &request) {
					return webIf->execute(&request, this);
				});
	}
	this->httpServer->listen(QHostAddress::Any, 8000);
    m_pThreadPool.reset(new qx::service::QxThreadPool());
    QObject::connect(m_pThreadPool.get(), SIGNAL(error(const QString &, qx::service::QxTransaction_ptr)), this, SLOT(onError(const QString &, qx::service::QxTransaction_ptr)));
    m_pThreadPool->start();
	ConsoleInput *input = new ConsoleInput();
	connect(this, &Application::startInput, input, &ConsoleInput::execute);
	connect(input, &ConsoleInput::input, this, &Application::handleUserInput);
	input->moveToThread(&inputThread);
	inputThread.start();
	emit startInput();
}

void Application::onError(const QString & err, qx::service::QxTransaction_ptr transaction)
{
   qDebug() << QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm") + " : " + err;
}
void Application::registerAuthProvider(AuthProviderInterface *authProvider) {
	authProviders.append(authProvider);
}

bool Application::isUserAuthorized(QString user, QString authObject,
		QMap<QString, QVariant> params) {
	int globalAuthState = -1;
	for (AuthProviderInterface *authProvider : this->authProviders) {
		int authState = authProvider->isUserAuthorized(user, authObject, params,
				this);
		if (authState > globalAuthState) {
			globalAuthState = authState;
		}
	}
	switch (globalAuthState) {
	case -1:
		return false;
		break;
	case 0:
		return true;
	case 1:
		return false;
	default:
		return false;
		break;
	}

}
QObject * Application::getValue(QString valueName){
	if(!this->genericValues.contains(valueName)){
		return nullptr;
	}
	return this->genericValues[valueName];
}

QList<QObject *> Application::getValues(QString valueName) {
	if(!this->genericListValues.contains(valueName)){
			return QList<QObject *>();
		}
		return this->genericListValues[valueName];
}

void Application::setValue(QString valueName, QObject * value) {
	if(!this->genericValues.contains(valueName)){
			this->genericValues.insert(valueName, value);
		}
    this->genericValues[valueName] = value;

}

void Application::addValue(QString valueName, QObject * value) {
	if(!this->genericListValues.contains(valueName)){
				this->genericListValues.insert(valueName, QList<QObject *>());
			}
	this->genericListValues[valueName].append(value);
}

#include "moc_application.cpp"
