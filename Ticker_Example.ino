#include "BpmTicker.h"
#include "math.h"

BpmTicker *ticker;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);

  ticker = new BpmTicker(120, 4, 40, onTick);
  ticker->startTicking();
}

void loop() {
  ticker->doTheThing();

  if (ticker->getTimeSinceLastTick() > 30){
    digitalWrite(LED_BUILTIN, LOW);
  }

  //Serial.print(ticker->getTimeToNextTick());Serial.print(",");
  //Serial.print(ticker->getTimeSinceLastTick());Serial.print(",");
  //Serial.println();
}

void onTick(float tickCount, long tickDelay) {
  if (fmod(tickCount, 1) == 0){
    digitalWrite(LED_BUILTIN, HIGH);    
  }
  
  Serial.print(tickDelay);Serial.print(",");
  Serial.print(fmod(tickCount, 1) == 0);Serial.print(",");
  Serial.println();
}
