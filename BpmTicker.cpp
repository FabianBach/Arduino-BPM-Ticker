#include "BpmTicker.h"

BpmTicker::BpmTicker(int bpm, int beatResolution, int precisionTime, fptr callback){
  this->beatResolution = beatResolution;
  this->precisionTime = precisionTime;
  this->callback = callback;

  this->reset();
  this->setBPM(bpm);
}

BpmTicker::~BpmTicker() {} // destructor

void BpmTicker::doTheThing(){
  if (!this->isTicking){ return; }
  
  unsigned long now;
  unsigned long nextTickStamp = this->getTimeOfNextTick();
  long timeToNextTick = this->getTimeToNextTick();

  if(timeToNextTick > 0 && timeToNextTick < this->precisionTime){
    // if very short time is left, just wait right here to make sure not to miss the beat
    delay(timeToNextTick);
    timeToNextTick = this->getTimeToNextTick();
  }

  if (timeToNextTick <= 0){
    this->lastTickStamp = nextTickStamp; // maybe not true, but this is when it should have ticked
    this->nextTickStamp = nextTickStamp + (int)this->tickDuration;
    this->tickCount = this->tickCount + (1/(float)this->beatResolution);

    // Calling the callback containing the count and the delay of the actual tick
    this->callback(this->tickCount, timeToNextTick);
  }
}

void BpmTicker::setBPM(int newBPM){
  this->bpm = newBPM;
  this->tickDuration = 60000 / newBPM / this->beatResolution;
  this->nextTickStamp = this->isTicking ? (this->lastTickStamp + (int)this->tickDuration) : 0;
}

unsigned long BpmTicker::getTickCount(){
  return this->tickCount;
}

unsigned long BpmTicker::getTimeOfNextTick(){
  return this->nextTickStamp;
}

long BpmTicker::getTimeToNextTick(){
  return this->getTimeOfNextTick() - millis();
}

unsigned long BpmTicker::getTimeSinceLastTick(){
  return millis() - this->lastTickStamp;
}

void BpmTicker::startTicking(){
  this->isTicking = true;
  this->doTheThing();
}

void BpmTicker::stopTicking(){
  this->reset();
}

void BpmTicker::reset(){
  this->isTicking = false;
  this->lastTickStamp = -1;
  this->nextTickStamp = 0;
  this->tickCount = 0;  
}
