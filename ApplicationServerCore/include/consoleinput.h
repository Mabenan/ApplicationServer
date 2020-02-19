#ifndef CONSOLEINPUT_H
#define CONSOLEINPUT_H
#include <string>
#include <iostream>
#include <QObject>

class ConsoleInput : public QObject
{    Q_OBJECT
 public:
     std::string command;
     ConsoleInput(QObject *parent = nullptr);
 public slots:
     void execute()
     {
         do
         {
             std::getline(std::cin, this->command);
             if(this->command == "stop"){
                 break;
             }
             emit input(QString(this->command.c_str()));
         } while (1 == 1);
             emit input(QString(this->command.c_str()));
             return;
     }

 signals:
     void input(QString command);
};

#endif // CONSOLEINPUT_H
