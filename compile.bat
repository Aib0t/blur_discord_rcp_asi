goto start
// "best" way: llvm : clang 13, compile for win32:
clang++ --target=i686-pc-windows-msvc -Wall -fms-compatibility -o build\blur_rpc.asi -I include -shared src\blur_rpc.cpp -L lib -l discord-rpc

// have not really looked at yet
clang-cl -Wall -fms-compatibility -MD -o build\blur-rpc.asi -I include -shared src\blur_rpc.cpp lib\discord-rpc.lib

// working: (ish)
%comspec% /k "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars32.bat"
%comspec% /k "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvars32.bat"
cl -I include /D_USRDLL /D_WINDLL /EHcs src/blur_rpc.cpp lib/discord-rpc.lib /MD /link  /DLL /OUT:build/blur_rpc.asi

:start

clang++ --target=i686-pc-windows-msvc -Wall -fms-compatibility -o build\blur_rpc.asi -I include -shared src\blur_rpc.cpp -L lib -l discord-rpc
