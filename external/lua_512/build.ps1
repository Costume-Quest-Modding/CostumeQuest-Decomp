# Needs visual studio powershell x86

New-Item -ItemType Directory -Force -Path obj | Out-Null

Push-Location src
& cl.exe /nologo /c /W3 /D_CRT_SECURE_NO_DEPRECATE /MT /O2 /Fo..\obj\ lapi.c lcode.c ldebug.c ldo.c ldump.c lfunc.c lgc.c llex.c lmem.c lobject.c lopcodes.c lparser.c lstate.c lstring.c ltable.c ltm.c lundump.c lvm.c lzio.c lauxlib.c lbaselib.c ldblib.c liolib.c lmathlib.c loslib.c lstrlib.c ltablib.c loadlib.c linit.c
Pop-Location

$objs = Get-ChildItem obj\*.obj | Select-Object -ExpandProperty FullName
& lib.exe /nologo /OUT:lua_512.lib @objs