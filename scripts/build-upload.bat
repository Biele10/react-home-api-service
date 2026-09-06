@echo off
setlocal EnableDelayedExpansion

REM ==========================================
REM Samaritan - Build and Upload
REM ==========================================

set "ROOT=%~dp0.."

echo.
echo ==========================================
echo Samaritan - Build and Upload
echo ==========================================
echo.

REM ==========================================
REM Raspberry Pi connection
REM ==========================================

set "PI_HOST=ubuntu@192.168.1.88"
set /p "PI_HOST=Enter Raspberry Pi SSH host [ubuntu@192.168.1.88]: "

set "PI_PORT=22"
set /p "PI_PORT=Enter SSH port [22]: "

echo.

echo Raspberry Pi:
echo   Host: %PI_HOST%
echo   Port: %PI_PORT%
echo.

REM ==========================================
REM Paths
REM ==========================================

set "PI_WEB=/var/www/Samaritan"
set "LOCAL_BUILD=%ROOT%\Samaritan-Build"

echo.
echo ==========================================
echo Samaritan - Build and Upload
echo ==========================================
echo.

REM ==========================================
REM Check required Windows tools
REM ==========================================

where ssh >nul 2>&1

if errorlevel 1 (
    echo [FAIL] OpenSSH client was not found.
    echo.
    echo Install/enable the Windows OpenSSH Client and try again.
    exit /b 1
)

where scp >nul 2>&1

if errorlevel 1 (
    echo [FAIL] SCP was not found.
    echo.
    echo Install/enable the Windows OpenSSH Client and try again.
    exit /b 1
)

echo [ OK ] OpenSSH found.
echo [ OK ] SCP found.

REM ==========================================
REM Check build directory
REM ==========================================

if not exist "%LOCAL_BUILD%" (
    echo.
    echo [FAIL] Samaritan-Build does not exist.
    echo.
    echo Run create-build.bat first.
    exit /b 1
)

echo [ OK ] Samaritan-Build found.

REM ==========================================
REM Check firmware
REM ==========================================

if not exist "%LOCAL_BUILD%\firmware\firmware.hex" (
    echo.
    echo [FAIL] Arduino firmware was not found.
    echo.
    echo Run create-build.bat first.
    exit /b 1
)

echo [ OK ] Arduino firmware found.

REM ==========================================
REM Check existing Arduino configuration
REM ==========================================

echo.
echo ==========================================
echo Checking Arduino configuration...
echo ==========================================
echo.

set "CONFIGURED=0"

ssh "%PI_HOST%" "if [ -f %PI_WEB%/daemon/code/config.hpp ] && grep -q 'SERIAL_PATH' %PI_WEB%/daemon/code/config.hpp; then exit 0; else exit 1; fi"

if not errorlevel 1 (
    set "CONFIGURED=1"

    echo [ OK ] Existing Arduino configuration found.
    echo [INFO] Existing SERIAL_PATH will be preserved.
) else (
    echo [INFO] Arduino SERIAL_PATH is not configured.
    echo [INFO] Arduino will be detected automatically.
)

REM ==========================================
REM Preserve existing config.hpp
REM ==========================================

if "!CONFIGURED!"=="1" (
    echo.
    echo [INFO] Preserving existing config.hpp...

    ssh "%PI_HOST%" "sudo cp %PI_WEB%/daemon/code/config.hpp /tmp/samaritan-config.hpp"

    if errorlevel 1 (
        echo.
        echo [FAIL] Failed to preserve existing config.hpp.
        exit /b 1
    )

    echo [ OK ] Existing config.hpp preserved.
)

REM ==========================================
REM Prepare deployment directory
REM ==========================================

echo.
echo ==========================================
echo Preparing Samaritan deployment...
echo ==========================================
echo.

ssh "%PI_HOST%" "sudo rm -rf %PI_WEB% && sudo mkdir -p %PI_WEB% && sudo chown ubuntu:ubuntu %PI_WEB% && sudo chmod 755 %PI_WEB%"

if errorlevel 1 (
    echo.
    echo [FAIL] Failed to prepare Samaritan deployment directory.
    exit /b 1
)

echo [ OK ] Deployment directory prepared.

REM ==========================================
REM Upload Samaritan build
REM ==========================================

echo.
echo ==========================================
echo Uploading Samaritan...
echo ==========================================
echo.

scp -r "%LOCAL_BUILD%\." "%PI_HOST%:%PI_WEB%/"

if errorlevel 1 (
    echo.
    echo [FAIL] Failed to deploy Samaritan.
    exit /b 1
)

echo.
echo [ OK ] Samaritan deployed.

echo.
echo ==========================================
echo Adjusting deployment permissions...
echo ==========================================
echo.

ssh "%PI_HOST%" "sudo chmod -R a+rX %PI_WEB%"
if errorlevel 1 (
    echo.
    echo [FAIL] Failed to set deployment permissions.
    exit /b 1
)

echo [ OK ] Deployment permissions configured.

REM ==========================================
REM Restore existing config.hpp
REM ==========================================

if "!CONFIGURED!"=="1" (
    echo.
    echo ==========================================
    echo Restoring Arduino configuration...
    echo ==========================================
    echo.

    ssh "%PI_HOST%" "sudo mv /tmp/samaritan-config.hpp %PI_WEB%/daemon/code/config.hpp"

    if errorlevel 1 (
        echo.
        echo [FAIL] Failed to restore config.hpp.
        exit /b 1
    )

    echo [ OK ] Existing config.hpp restored.
)

REM ==========================================
REM Detect Arduino
REM ==========================================

echo.
echo ==========================================
echo Detecting Arduino...
echo ==========================================
echo.

set "ARDUINO_COUNT=0"
set "ARDUINO_SERIAL="

for /f "delims=" %%A in ('ssh "%PI_HOST%" "find /dev/serial/by-id -maxdepth 1 -type l -name '*Arduino*' -print"') do (
    set /a ARDUINO_COUNT+=1
    set "ARDUINO_SERIAL=%%A"
)

if "!ARDUINO_COUNT!"=="0" (
    echo.
    echo [FAIL] No Arduino was detected.
    echo.
    echo Connect the Arduino to the Raspberry Pi and run deployment again.
    exit /b 1
)

if not "!ARDUINO_COUNT!"=="1" (
    echo.
    echo [FAIL] Multiple Arduino devices were detected.
    echo.
    echo Detected devices:
    ssh "%PI_HOST%" "find /dev/serial/by-id -maxdepth 1 -type l -name '*Arduino*' -print"
    echo.
    echo Please leave only one Arduino connected and try again.
    exit /b 1
)

echo [ OK ] Arduino detected:
echo        !ARDUINO_SERIAL!

REM ==========================================
REM Generate config.hpp if required
REM ==========================================

if "!CONFIGURED!"=="0" (

    echo.
    echo ==========================================
    echo Generating Samaritan configuration...
    echo ==========================================
    echo.

    set "CONFIG_FILE=%TEMP%\samaritan-config.hpp"

    (
        echo #pragma once
        echo.
        echo constexpr const char* SERIAL_PATH = "!ARDUINO_SERIAL!";
        echo.
        echo constexpr const char* SOCKET_PATH = "/run/samaritan/samaritan.sock";
    ) > "!CONFIG_FILE!"

    if errorlevel 1 (
        echo.
        echo [FAIL] Failed to generate temporary config.hpp.
        exit /b 1
    )

    echo [ OK ] Temporary config.hpp generated.

    echo [INFO] Uploading config.hpp...

    scp "!CONFIG_FILE!" "%PI_HOST%:/tmp/samaritan-config.hpp"

    if errorlevel 1 (
        echo.
        echo [FAIL] Failed to upload config.hpp.
        del /q "!CONFIG_FILE!" >nul 2>&1
        exit /b 1
    )

    echo [ OK ] config.hpp uploaded.

    echo [INFO] Installing config.hpp...

    ssh "%PI_HOST%" "sudo mv /tmp/samaritan-config.hpp %PI_WEB%/daemon/code/config.hpp"

    if errorlevel 1 (
        echo.
        echo [FAIL] Failed to install config.hpp.
        del /q "!CONFIG_FILE!" >nul 2>&1
        exit /b 1
    )

    del /q "!CONFIG_FILE!" >nul 2>&1

    echo [ OK ] config.hpp installed.
)

REM ==========================================
REM Upload Arduino firmware
REM ==========================================

echo.
echo ==========================================
echo Uploading Arduino firmware...
echo ==========================================
echo.

ssh "%PI_HOST%" "sudo avrdude -p atmega328p -c arduino -P '!ARDUINO_SERIAL!' -b 115200 -D -U flash:w:%PI_WEB%/firmware/firmware.hex:i"

if errorlevel 1 (
    echo.
    echo [FAIL] Arduino firmware upload failed.
    exit /b 1
)

echo.
echo [ OK ] Arduino firmware uploaded.

REM ==========================================
REM Compile C++ daemon
REM ==========================================

echo.
echo ==========================================
echo Compiling C++ daemon...
echo ==========================================
echo.

ssh "%PI_HOST%" "cd %PI_WEB%/daemon && sudo mkdir -p build && sudo g++ -std=c++17 code/main.cpp code/UnixSocket/UnixSocket.cpp code/ArduinoSerial/ArduinoSerial.cpp -o build/samaritan-daemon"

if errorlevel 1 (
    echo.
    echo [FAIL] C++ daemon compilation failed.
    exit /b 1
)

echo [ OK ] C++ daemon compiled.

REM ==========================================
REM Restart Samaritan daemon
REM ==========================================

echo.
echo ==========================================
echo Restarting Samaritan daemon...
echo ==========================================
echo.

ssh "%PI_HOST%" "sudo systemctl restart samaritan-daemon"

if errorlevel 1 (
    echo.
    echo [FAIL] Failed to restart Samaritan daemon.
    exit /b 1
)

echo [ OK ] Samaritan daemon restarted.

REM ==========================================
REM Restart Apache
REM ==========================================

echo.
echo ==========================================
echo Restarting Apache...
echo ==========================================
echo.

ssh "%PI_HOST%" "sudo systemctl restart apache2"

if errorlevel 1 (
    echo.
    echo [FAIL] Failed to restart Apache.
    exit /b 1
)

echo [ OK ] Apache restarted.

REM ==========================================
REM Finished
REM ==========================================

echo.

echo React application: deployed
echo PHP backend: deployed
echo Arduino firmware: uploaded
echo Arduino configuration: preserved/generated
echo C++ daemon: compiled and restarted
echo Apache: restarted

endlocal
exit /b 0