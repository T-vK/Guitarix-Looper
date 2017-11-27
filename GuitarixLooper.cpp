#include <GuitarixLooper.h>

GuitarixLooper::GuitarixLooper(byte channel, byte *tapeRecord, byte *tapePlay, byte *tapeErase) {
    this->channel = channel;
    this->tapeRecord = tapeRecord;
    this->tapePlay = tapePlay;
    this->tapeErase = tapeErase;
}
void GuitarixLooper::recordStart(int tape) {
    MidiUSB.sendMIDI({0x0B, 0xB0 | this->channel, this->tapeRecord[tape], this->start});
}
void GuitarixLooper::recordStop(int tape) {
    MidiUSB.sendMIDI({0x0B, 0xB0 | this->channel, this->tapeRecord[tape], this->stop});
}
void GuitarixLooper::play(int tape) {
    MidiUSB.sendMIDI({0x0B, 0xB0 | this->channel, this->tapePlay[tape], this->start});
}
void GuitarixLooper::pause(int tape) {
    MidiUSB.sendMIDI({0x0B, 0xB0 | this->channel, this->tapePlay[tape], this->stop});
}
void GuitarixLooper::erase(int tape) {
    MidiUSB.sendMIDI({0x0B, 0xB0 | this->channel, this->tapeErase[tape], this->start});
    MidiUSB.sendMIDI({0x0B, 0xB0 | this->channel, this->tapeErase[tape], this->stop});
}
void GuitarixLooper::send() {
    MidiUSB.flush();
}