@ECHO OFF
cl.exe /EHsc LoaderLock.cpp ../../../Core/MemWarsServicesCore.cpp ../../../Core/MemWarsCore.c /link user32.lib ntdll.lib Advapi32.lib Shlwapi.lib