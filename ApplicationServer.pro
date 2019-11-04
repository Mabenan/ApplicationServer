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
