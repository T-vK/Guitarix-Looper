#include <GuitarixSingleButtonLooper.h>

GuitarixSingleButtonLooper::GuitarixSingleButtonLooper(byte channel, byte *tapeRecord, byte *tapePlay, byte *tapeErase, int buttonPin, int ledPin) {

    this->guitarixLooper = new GuitarixLooper(channel, tapeRecord, tapePlay, tapeErase);
    this->buttonPin = buttonPin;
    this->ledPin = ledPin;

    pinMode(this->buttonPin, INPUT_PULLUP);
    pinMode(this->ledPin, OUTPUT);
}

void GuitarixSingleButtonLooper::startRecordBaseLayer(void) {
    Serial.println("GuitarixSingleButtonLooper::startRecordBaseLayer");
    this->currentLayerStart = millis();
    this->guitarixLooper->recordStart(this->currentLayer);
    this->guitarixLooper->send();
    digitalWrite(this->ledPin, LOW);
    this->recordingLayer = true;
}
void GuitarixSingleButtonLooper::stopRecordBaseLayer(void) {
    Serial.println("GuitarixSingleButtonLooper::stopRecordBaseLayer");
    this->guitarixLooper->recordStop(this->currentLayer);
    this->guitarixLooper->play(this->currentLayer);
    this->baseLayerLength = millis() - this->currentLayerStart; 
    this->guitarixLooper->send();
    this->currentLayer++;
    digitalWrite(this->ledPin, HIGH);
    this->recordingLayer = false;
}
void GuitarixSingleButtonLooper::recordNewLayer(void) {
    Serial.println("GuitarixSingleButtonLooper::recordNewLayer");
    if (this->currentLayer > 0 && this->currentLayer <= 3) {
        this->currentLayerStart = millis();
        this->guitarixLooper->recordStart(this->currentLayer);
        this->guitarixLooper->send();
        this->recordingLayer = true;
        digitalWrite(this->ledPin, LOW);
    }
}
void GuitarixSingleButtonLooper::stopRecording(void) {
    Serial.println("GuitarixSingleButtonLooper::stopRecording");
    if (this->recordingLayer) {
        this->currentLayerStart = millis();
        this->guitarixLooper->recordStop(this->currentLayer);
    this->guitarixLooper->play(this->currentLayer);
        this->guitarixLooper->send();
        this->recordingLayer = false;
        this->currentLayer++;
        digitalWrite(this->ledPin, HIGH);
    }
}
void GuitarixSingleButtonLooper::removeLastLayer(void) {
    Serial.println("GuitarixSingleButtonLooper::removeLastLayer");
    if (this->currentLayer > 0) {
        this->currentLayer--;
        this->guitarixLooper->erase(this->currentLayer);
    // workaround to reset the seekbar thingy:
        this->guitarixLooper->play(this->currentLayer);
        this->guitarixLooper->pause(this->currentLayer);
        this->guitarixLooper->send();
    }
}
void GuitarixSingleButtonLooper::reset(void) {
    Serial.println("GuitarixSingleButtonLooper::reset");
    this->currentLayer = 0;
    this->recordingLayer = false;
    for (int i=0; i<=3; i++) {
        this->guitarixLooper->recordStop(i);
        this->guitarixLooper->pause(i);
        this->guitarixLooper->erase(i);
    // workaround to really reset guitarix
    this->guitarixLooper->play(i);
    this->guitarixLooper->pause(i);
    }
    this->guitarixLooper->send();
}


void GuitarixSingleButtonLooper::loop(unsigned long now) {
    if (this->recordingLayer && this->currentLayer > 0 && now >= this->currentLayerStart+this->baseLayerLength) { // recording layer (excl base layer) and base layer length is reached
        this->stopRecording();
    }

    int buttonState = digitalRead(this->buttonPin);
    if (buttonState == LOW) { // button is pressed down
        if (this->lastButtonState == HIGH) { // button was not pressed down
            Serial.println("Button pressed");
            if (now > this->lastButtonPressedTime+this->pressDelay) { // if >70ms have passed since last press
                if (now > this->lastButtonPressedTime+this->doublepressTimeout) { // if >1s has passed since last press
                    // normal single press
                    if (this->recordingLayer) {
                        if (this->currentLayer == 0) {
                            this->stopRecordBaseLayer();
                        }
                    } else {
                        if (this->currentLayer == 0) {
                            this->startRecordBaseLayer();
                        } else {
                            this->recordNewLayer();
                        }
                    }
                } else { // double pressed
                    if (this->recordingLayer) {
                        this->stopRecording();
                        this->removeLastLayer();
                        if (this->currentLayer > 0) {
                            this->removeLastLayer();
                        }
                    } else {
                        this->removeLastLayer();
                    }
                }
                this->lastButtonPressedTime = now;
                this->buttonDownSince = 0;
            }
        } else { // user keeps holding the button down
            if (now > this->buttonDownSince+this->holdDelay) { // user held down for 2s
                this->reset();
                this->buttonDownSince = 0; // "reset the hold timer"
            }
        }
        if (this->buttonDownSince == 0)
            this->buttonDownSince = now;
    } else { // button not down
        this->buttonDownSince = 0;
    }

    this->lastButtonState = buttonState;
}
