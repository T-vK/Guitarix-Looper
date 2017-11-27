# Guitarix Looper

## Work in progress
- This library is not finished yet and has not been tested so far.

## What does it do

This library makes your Arduino register as a Midi device on your computer through its USB port to send MIDI commands to Guitarix in order to control the Looper module.  

Please note that not all Arduinos are USBMIDI compatible. I have used a cheap Arduino Pro Micro clone which acts like an Arduino Leonardo.  
Arduino clones with a CH340 chip will probably not work. The official Arduino UNO, Pro Micro, Nano, MEGA and Lilipad etc should work fine. Pro Mini lacks a USB port...  

[Refer to the example](examples/SingeButtonLooper/SingleButtonLooper.ino) for more information on how to set up Guitarix for the MIDI messages and your Arduino MIDI device with JACK. 
