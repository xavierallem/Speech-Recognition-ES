
#include "model.h"
#define MIC A0
#define NUM_SAMPLES 64
#define SAMPLING_FREQUENCY 1024
#define INTERVAL 5
#define SOUND_THRESHOLD 4

unsigned int samplingPeriod;
unsigned long microSeconds;

int32_t backgroundSound;
float features[NUM_SAMPLES];

Eloquent::ML::Port::SVM svm;

void setup() {
    Serial.begin(115200);
    pinMode(MIC, INPUT);
   

    samplingPeriod = round(1000000*(1.0/SAMPLING_FREQUENCY));
    calibrate();

}

void loop() {
    if (!soundDetected()) {
        delay(10);
        return;
    }

  

if(digitalRead(MIC)==HIGH){
    Serial.print("You said ");
    Serial.println(svm.predictLabel(svm.predict(features)));
   
}
    delay(1000);


}


int16_t readMic() {
    return analogRead(MIC);
    return (analogRead(MIC) - 512) >> 2;
}


void calibrate() {
    for (int i = 0; i < 200; i++)
        backgroundSound += readMic();

    backgroundSound /= 200;

   
}

bool soundDetected() {
    return abs(readMic() - backgroundSound) >= SOUND_THRESHOLD;
}
