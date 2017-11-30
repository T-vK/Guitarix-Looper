/* This example will make the Arduino act as a Midi Looper Pedal in conjunction with Guitarix.
 * To use the Guitarix Looper library you also need to install the USBMIDI (You can find it in the Library Manager of the Arduino IDE).
 * Make sure to run a2jmidid from the terminal and also to run Guitarix, then in JACK connect your Arduino to gx_head_amp in the MIDI tab.
 * Then in Guitarix in the looper module make a middle click on the record button of every tape, entering the codes 
 * 40 (for tape 1), 41 (for tape 2), 42 (tape 3), 43 (tape 4),
 * Then do the same for the play button of every tape using these codes: 44,45,46,47
 * And finally do the same for the erase button of every tape using these codes: 48,49,50,51
 */

#include <GuitarixSingleButtonLooper.h>

int LOOPER_BUTTON = 14;
int RECORDING_LED =  13;

byte MIDI_CHANNEL = 0; // channel 1

byte LOOPER_TAPE_RECORD_CODES[4] = {40,41,42,43};
byte LOOPER_TAPE_PLAY_CODES[4] = {44,45,46,47};
byte LOOPER_TAPE_ERASE_CODES[4] = {48,49,50,51};

GuitarixSingleButtonLooper guitarixSingleButtonLooper(MIDI_CHANNEL, LOOPER_TAPE_RECORD_CODES, LOOPER_TAPE_PLAY_CODES, LOOPER_TAPE_ERASE_CODES, LOOPER_BUTTON, RECORDING_LED);

void setup() {
    Serial.begin(115200);
    Serial.println("MIDI device ready!");
}

void loop() {
    unsigned long now = millis();
    guitarixSingleButtonLooper.loop(now);
}