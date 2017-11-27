#include <GuitarixSingleButtonLooper.h>

GuitarixSingleButtonLooper::GuitarixSingleButtonLooper(byte channel, byte *tapeRecord, byte *tapePlay, byte *tapeErase, int buttonPin, int ledPin) {

    this->guitarixLooper = new GuitarixLooper(channel, tapeRecord, tapePlay, tapeErase);
    this->buttonPin = buttonPin;
    this->ledPin = ledPin;

    pinMode(this->buttonPin, INPUT_PULLUP);
    pinMode(this->ledPin, OUTPUT);
}

void GuitarixSingleButtonLooper::startRecordBaseLayer(void) {
    this->currentLayerStart = millis();
    this->guitarixLooper->recordStart(this->currentLayer);
    this->guitarixLooper->send();
    digitalWrite(this->ledPin, HIGH);
}
void GuitarixSingleButtonLooper::stopRecordBaseLayer(void) {
    this->guitarixLooper->recordStop(this->currentLayer);
    for (int i=1; i<=4; i++) {
        this->guitarixLooper->play(i);
    }
    this->baseLayerLength = millis() - this->currentLayerStart; 
    this->guitarixLooper->send();
    this->currentLayer++;
    digitalWrite(this->ledPin, LOW);
}
void GuitarixSingleButtonLooper::recordNewLayer(void) {
    if (this->currentLayer > 1 && this->currentLayer <= 4) {
        this->currentLayerStart = millis();
        this->guitarixLooper->recordStart(this->currentLayer);
        this->guitarixLooper->send();
        this->currentLayer++;
        this->recordingLayer = true;
        digitalWrite(this->ledPin, HIGH);
    }
}
void GuitarixSingleButtonLooper::stopRecording(void) {
    if (this->recordingLayer) {
        this->currentLayerStart = millis();
        this->guitarixLooper->recordStop(this->currentLayer);
        this->guitarixLooper->send();
        this->recordingLayer = false;
        digitalWrite(this->ledPin, LOW);
    }
}
void GuitarixSingleButtonLooper::removeLastLayer(void) {
    if (this->currentLayer > 1) {
        this->currentLayer--;
        this->guitarixLooper->erase(this->currentLayer);
        this->guitarixLooper->send();
    }
}
void GuitarixSingleButtonLooper::reset(void) {
    this->currentLayer = 1;
    this->recordingLayer = false;
    for (int i=1; i<=4; i++) {
        this->guitarixLooper->recordStop(i);
        this->guitarixLooper->pause(i);
        this->guitarixLooper->erase(i);
    }
    this->guitarixLooper->send();
}


void GuitarixSingleButtonLooper::loop(void) {
    int now = millis();
    if (this->recordingLayer && this->currentLayer > 1 && now >= this->currentLayerStart+this->baseLayerLength) { // recording layer (excl base layer) and base layer length is reached
        this->stopRecording();
    }

    int buttonState = digitalRead(this->buttonPin);
    
    if (buttonState == LOW) { // button is pressed down
        if (this->lastButtonState == HIGH) { // button was not pressed down
            if (now > this->lastButtonPressedTime+this->pressDelay) { // if >70ms have passed since last press
                if (now > this->lastButtonPressedTime+this->doublepressTimeout) { // if >1s has passed since last press
                    // normal single press
                    if (this->recordingLayer) {
                        if (this->currentLayer == 1) {
                            this->stopRecordBaseLayer();
                        }
                    } else {
                        if (this->currentLayer == 1) {
                            this->startRecordBaseLayer();
                        } else {
                            this->recordNewLayer();
                        }
                    }
                } else { // double pressed
                    if (this->recordingLayer) {
                        this->stopRecording();
                        this->removeLastLayer();
                        if (this->currentLayer > 1) {
                            this->removeLastLayer();
                        }
                    } else {
                        this->removeLastLayer();
                    }
                }
                this->lastButtonPressedTime = now;
            }
        } else { // user keeps holding the button down
            if (now > this->lastButtonPressedTime+this->holdDelay) { // user held down for a long time
                this->reset();
                this->lastButtonPressedTime = now; // "reset the hold timer"
            }
        }
    }

    this->lastButtonState = buttonState;
}
