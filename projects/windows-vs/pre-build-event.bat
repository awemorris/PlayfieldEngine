@echo off

if not exist "dx12headers\" (
    git clone https://github.com/microsoft/DirectX-Headers.git dx12headers
    if %ERRORLEVEL% == 0 goto NEXT
    echo Cannot clone dx12headers.
    exit 1
)

:NEXT

if not exist "libroot\" (
    echo Making libraries...
    call build-libs.bat
    if %ERRORLEVEL% == 0 goto END
    echo Cannot build libraries.
    exit 1
)

:END
