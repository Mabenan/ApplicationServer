#ifndef CONSOLEINPUT_H
#define CONSOLEINPUT_H
#include <string>
#include <iostream>
#include <QObject>
#include <QString>

class ConsoleInput : public QObject
{    Q_OBJECT
 public:
     std::string command;
     ConsoleInput(QObject *parent = nullptr);
 public slots:
     void execute();

 signals:
     void input(QString command);
};

#endif // CONSOLEINPUT_H
