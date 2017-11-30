# Guitarix Looper

## Work in progress
There are some bugs. Timing is not perfect and you might have to manually press the play button for each tape twice in order to reset the "seekbar" properly (it might just be a visual bug though).


## Credits
A big Thanks to snappy46 who told me how the Looper device can be controlled in the first place! Please take a look at his [GuitarixMidiController](https://github.com/snappy46/GuitarixMidiController) which is a very interesting project! Also look at the dev branch for the Looper functionality. You might also want to look at his Readme because he has screenshots that might explain the process of how to connect the Arduino Midi device with Guitarix better to you.

## What does it do

This library makes your Arduino register as a Midi device on your computer through its USB port to send MIDI commands to Guitarix in order to control the Looper module.  

Please note that not all Arduinos are USBMIDI compatible. I have used a cheap Arduino Pro Micro clone which acts like an Arduino Leonardo.  
Arduino clones with a CH340 chip will probably not work. The official Arduino UNO, Pro Micro, Nano, MEGA and Lilipad etc should work fine. Pro Mini lacks a USB port...  


## How does it work

It works like a normal single button Looper Pedal:

Press the button for the first time to start recording the first layer. Press it for the second time to stop recording and play it in a loop.
Press the button again to record another layer on top of the first one. (The recording will automatically stop so that both layers have the exact same length).
You can repeat the last step two mroe times, so you would have 4 layers. That's the maximum (limit by Guitarix).

By double pressing the button you can delete the last layer (usually if you messed up).  
By long pressing you can reset everything.

## How to install the library
In your Arduino IDE go to `Sketch->Include Library->Manage Libraries->[search for MIDIUSB and install the latest version]`
Next [download the librabry as a zip file](https://github.com/T-vK/Guitarix-Looper/archive/master.zip)
Then again in your Arduino IDE go to `Sketch->Include Library->Add a .ZIP Library` and select the file you just downloaded.
Finally (again in the IDE) go to `File->Examples->Guitarix Looper->Examples->SingleButtonLooper`.  
Adjust the pins for the looper button and the led.  

## How to connect the Arduino Midi device with Guitarix
- run `qjackctl` 
- run Guitarix
- run `a2jmidid -e` 
- In qjackctl click `Connect` -> `click MIDI` -> (on the left panel) open the a2j tree and select your Arduino -> (on the right panel) select `gx_head_amp` -> click `Connect` in the same window.

## Set up Guitarix for the Midi device
In Guitarix in the looper module make a middle click on the record button of every tape, entering the codes 
40 (for tape 1), 41 (for tape 2), 42 (tape 3), 43 (tape 4),
Then do the same for the play button of every tape using these codes: 44,45,46,47
And finally do the same for the erase button of every tape using these codes: 48,49,50,51


