TEMPLATE = subdirs

SUBDIRS += \
    ApplicationServer \
    ApplicationServerInterface \
    ApplicationServerListCommands

ApplicationServer.depends = ApplicationServerInterface
ApplicationServerListCommands.depends = ApplicationServerInterface