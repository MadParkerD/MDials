# MDials
An arduino based midi controller for hundreds of potentiometers.

Copyright - 2019, Madison Parker-Durost

## Explanation:
This project serves to allow many potentiometers and/or other measurement devices to be connected in large numbers to an arduino and exported in the form of midi over usb. 
This is accomplished by a form of analog multiplexing coupled with a means of sending midi control actions that are readable on a standard windows computer. 
Currently the Arduino MIDI Library https://github.com/FortySevenEffects/arduino_midi_library is being used for that function.

## Install:
See wiki: https://github.com/MadParkerD/MDials/wiki
## Use:
Code should be loaded onto the arduino and connected via usb to a windows(temporarily required) computer.

## Physical Materials:
Arduino Mega/Uno (16/8 analog pins)

Potentiometers (10k)

Wire

## Software/Libraries

Arduino MIDI Library: https://github.com/FortySevenEffects/arduino_midi_library

## LICENSE
This software is licensed under the gpl v3. A copy of the relevant license may be found in the top level directory of this git repository along with this README. A web version can currently be found at https://www.gnu.org/licenses/gpl-3.0.en.html
