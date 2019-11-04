#ifndef MESSAGELOGGER_H
#define MESSAGELOGGER_H

#include <QList>
#include <iostream>



class MessageLogger
{
public:
   static MessageLogger* instance ()
   {
      if (!_instance)
         _instance = new MessageLogger ();
      return _instance;
   }
   QList<QString> loggedMessages;

   void log(QString msg){
       this->loggedMessages.push_back(msg);
       std::string msgString = msg.toStdString();
       std::cout << msgString << std::endl;
   }
private:
   static MessageLogger* _instance;
   MessageLogger () { } /* verhindert, dass ein Objekt von außerhalb von N erzeugt wird. */
             // protected, wenn man von der Klasse noch erben möchte
   MessageLogger ( const MessageLogger& );
};
MessageLogger* MessageLogger::_instance = 0;
#endif // MESSAGELOGGER_H
