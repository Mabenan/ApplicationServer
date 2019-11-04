QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_findsplugins.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ApplicationServerInterface/ -lApplicationServerInterface
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ApplicationServerInterface/ -lApplicationServerInterface
else:unix: LIBS += -L$$OUT_PWD/../ApplicationServerInterface/ -lApplicationServerInterface

INCLUDEPATH += $$PWD/../ApplicationServerInterface
DEPENDPATH += $$PWD/../ApplicationServerInterface


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ApplicationServerCore/ -lApplicationServerCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ApplicationServerCore/ -lApplicationServerCore
else:unix: LIBS += -L$$OUT_PWD/../ApplicationServerCore/ -lApplicationServerCore

INCLUDEPATH += $$PWD/../ApplicationServerCore
DEPENDPATH += $$PWD/../ApplicationServerCore

HEADERS += \
    messagelogger.h
