@ECHO OFF
cl.exe /EHsc /LD InjectedDLL.cpp InjectedDLLHelperFuncs.cpp /I"C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include" /link /LIBPATH:"C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Lib\x64" user32.lib d3d9.lib d3dx9.lib