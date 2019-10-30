TEMPLATE = subdirs

SUBDIRS += \
    ApplicationServer \
    ApplicationServerCore \
    ApplicationServerInterface \
    ApplicationServerListCommands \
    ApplicationServerTest

ApplicationServer.depends = ApplicationServerCore
ApplicationServerCore.depends = ApplicationServerInterface
ApplicationServerListCommands.depends = ApplicationServerInterface

ApplicationServerTest.depends = ApplicationServerCore ApplicationServerListCommands

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/ApplicationServerCore/release/ -lApplicationServerCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/ApplicationServerCore/debug/ -lApplicationServerCore
else:unix: LIBS += -L$$OUT_PWD/ApplicationServerCore/ -lApplicationServerCore

INCLUDEPATH += $$PWD/ApplicationServerCore
DEPENDPATH += $$PWD/ApplicationServerCore
