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
		emit input(QString(this->command.c_str()));
	} while (1 == 1);
	emit input(QString(this->command.c_str()));
	return;
}

#include "moc_consoleinput.cpp"
