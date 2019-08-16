@echo off
pushd %~dp0
set /p board="Uno(1) or Mega2560(2)?"
echo "Downloading"
powershell -Command "(New-Object Net.WebClient).DownloadFile('https://raw.githubusercontent.com/ddiakopoulos/hiduino/master/compiled_firmwares/arduino_midi.hex', 'arduino_midi.hex')"
IF "%board%"=="1" (
    powershell -Command "(New-Object Net.WebClient).DownloadFile('https://raw.githubusercontent.com/arduino/ArduinoCore-avr/master/firmwares/atmegaxxu2/Arduino-COMBINED-dfu-usbserial-atmega16u2-Uno-Rev3.hex', 'arduino-serial.hex')"
)
IF "%board%"=="2" (
    powershell -Command "(New-Object Net.WebClient).DownloadFile('https://raw.githubusercontent.com/arduino/ArduinoCore-avr/master/firmwares/atmegaxxu2/Arduino-COMBINED-dfu-usbserial-atmega16u2-Mega2560-Rev3.hex', 'arduino-serial.hex')"
)
pause
