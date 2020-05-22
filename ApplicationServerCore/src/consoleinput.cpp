#include <consoleinput.h>
#include <string>
#include <iostream>
#include <QObject>
#include <QString>

ConsoleInput::ConsoleInput(QObject *parent) :
		QObject(parent) {

}

void ConsoleInput::execute()
{
	do {
		std::getline(std::cin, this->command);
		if (this->command == "stop") {
			break;
		}
		Q_EMIT input(QString::fromLatin1(this->command.c_str()));
	} while (1 == 1);
	Q_EMIT input(QString::fromLatin1(this->command.c_str()));
}

#include "moc_consoleinput.cpp"
