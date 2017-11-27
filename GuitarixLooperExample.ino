#include "GuitarixSingleButtonLooper.h"

const int LOOPER_BUTTON = 14;
const int RECORDING_LED =  13;

const byte MIDI_CHANNEL = 0; // channel 1

const byte LOOPER_TAPE_RECORD_CODES[TAPE_COUNT] = {40,41,42,43};
const byte LOOPER_TAPE_PLAY_CODES[TAPE_COUNT] = {44,45,46,47};
const byte LOOPER_TAPE_ERASE_CODES[TAPE_COUNT] = {48,49,50,51};

GuitarixSingleButtonLooper guitarixSingleButtonLooper = new GuitarixSingleButtonLooper(MIDI_CHANNEL, LOOPER_TAPE_RECORD_CODES, LOOPER_TAPE_PLAY_CODES, LOOPER_TAPE_ERASE_CODES, LOOPER_BUTTON, RECORDING_LED);

void setup() {
    //Serial.begin(115200);
}

void loop() {
    guitarixSingleButtonLooper.loop();
}