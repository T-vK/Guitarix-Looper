#ifndef GuitarixLooper_h
#define GuitarixLooper_h

#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
 #include <pins_arduino.h>
#endif

#include <MIDIUSB.h>

class GuitarixLooper
{
public:
    static const byte start = 64;
    static const byte stop = 0;
    byte channel = 0;
    byte *tapeRecord;
    byte *tapePlay;
    byte *tapeErase;

    GuitarixLooper(byte channel, byte *tapeRecord, byte *tapePlay, byte *tapeErase);
    void recordStart(int tape);
    void recordStop(int tape);
    void play(int tape);
    void pause(int tape);
    void erase(int tape);
    void send(void);
};

#endif