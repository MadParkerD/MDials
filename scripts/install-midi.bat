@echo off
pushd %~dp0
set /p chip="ATmega16u2(1) or ATmega8u2(2)?"
set /p tru="Are you SURE you want to flash the hiduino firmware?(y/n)"
IF "%tru%"=="y" (
IF "%chip%"=="1" (
@echo on
    dfu-programmer atmega16u2 erase
    dfu-programmer atmega16u2 flash arduino_midi.hex
    dfu-programmer atmega16u2 reset
@echo off
   )
IF "%chip%"=="2" (
@echo on
    dfu-programmer atmega8u2 erase
    dfu-programmer atmega8u2 flash arduino_midi.hex
    dfu-programmer atmega8u2 reset
@echo off
   )
)
pause
