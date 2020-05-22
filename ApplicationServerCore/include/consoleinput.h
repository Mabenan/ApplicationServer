#ifndef CONSOLEINPUT_H
#define CONSOLEINPUT_H
#include <QObject>
#include <QString>
#include <iostream>
#include <string>

class ConsoleInput : public QObject {
  Q_OBJECT
private:
  std::string command;

public:
  ConsoleInput(QObject *parent = nullptr);
public Q_SLOTS:
  void execute();

Q_SIGNALS:
  void input(QString command);
};

#endif // CONSOLEINPUT_H
