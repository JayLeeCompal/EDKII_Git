@REM
@REM Project setup batch file
@REM
@echo off

REM ---------------------------------------------------------------------------------------------
REM Auto setting of WORKSPACE environment variable
REM ---------------------------------------------------------------------------------------------
pushd \ && set ROOT_DIR=%cd% && popd && pushd .
:SetWorkSpace
if "%cd%" == "%ROOT_DIR%" goto Next
cd ..
if not exist %cd%\BaseTools goto SetWorkSpace
set WORKSPACE=%cd%
:Next
set ROOT_DIR= && popd

REM ---------------------------------------------------------------------------------------------
REM Project dependent parameters
REM ---------------------------------------------------------------------------------------------
set TOOL_CHAIN=DEVTLS_VC10

If "%DEVTLS_DIR%" == "" goto DefASL_DIR
set ASL_PATH=%TOOL_DIR%\%DEVTLS_DIR%\Asl\Acpi5.0
goto SetArch

:DefASL_DIR
set ASL_PATH=D:\DEVTLS\Asl\Acpi5.0

:SetArch
set ARCH=IA32 X64

call H2ORev50.bat
