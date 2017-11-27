#ifndef GuitarixSingleButtonLooper_h
#define GuitarixSingleButtonLooper_h

#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
 #include <pins_arduino.h>
#endif

#include <GuitarixLooper.h>

class GuitarixSingleButtonLooper
{
public:
    GuitarixLooper *guitarixLooper;
    int currentLayer = 0;
    int currentLayerStart;
    int baseLayerLength;
    bool recordingLayer = false;
    int buttonPin;
    int ledPin;
    int lastButtonState = HIGH;
    int lastButtonPressedTime = 0;
    int pressDelay = 200;
    int doublepressTimeout = 1000;
    int holdDelay = 2000;

    GuitarixSingleButtonLooper(byte channel, byte *tapeRecord, byte *tapePlay, byte *tapeErase, int buttonPin, int ledPin);
    void loop(void);
    void startRecordBaseLayer(void);
    void stopRecordBaseLayer(void);
    void recordNewLayer(void);
    void removeLastLayer(void);
    void stopRecording(void);
    void reset(void);
};

#endif
