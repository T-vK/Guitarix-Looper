# Guitarix Looper

## Work in progress
- This library is not finished yet and has not been tested so far.

## Credits
A big Thanks to snappy46 who told me how the Looper device can be controlled in the first place! Please take a look at his [GuitarixMidiController](https://github.com/snappy46/GuitarixMidiController) which is a very interesting project! Also look at the dev branch for the Looper functionality.

## What does it do

This library makes your Arduino register as a Midi device on your computer through its USB port to send MIDI commands to Guitarix in order to control the Looper module.  

Please note that not all Arduinos are USBMIDI compatible. I have used a cheap Arduino Pro Micro clone which acts like an Arduino Leonardo.  
Arduino clones with a CH340 chip will probably not work. The official Arduino UNO, Pro Micro, Nano, MEGA and Lilipad etc should work fine. Pro Mini lacks a USB port...  

[Refer to the example](examples/SingeButtonLooper/SingleButtonLooper.ino) for more information on how to set up Guitarix for the MIDI messages and your Arduino MIDI device with JACK. 


## How does it work

It works like a normal single button Looper Pedal:

Press the button for the first time to start recording the first layer. Press it for the second time to stop recording and play it in a loop.
Press the button again to record another layer on top of the first one. (The recording will automatically stop so that both layers have the exact same length).
You can repeat the last step two mroe times, so you would have 4 layers. That's the maximum (limit by Guitarix).

By double pressing the button you can delete the last layer (usually if you messed up).  
By long pressing you can reset everything.
