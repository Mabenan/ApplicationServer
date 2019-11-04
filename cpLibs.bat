@ECHO OFF

for /r ApplicationServerInterface/ %%f in (*.dll) do (
    copy %%f ApplicationServer
    copy %%f ApplicationServerTest
)
for /r ApplicationServerCore/ %%f in (*.dll) do (
    copy %%f ApplicationServer
    copy %%f ApplicationServerTest
)