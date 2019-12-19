#ifndef BpmTicker_h
#define BpmTicker_h

#include "Arduino.h"

typedef void (*fptr)(float, long); // do I even need this?

class BpmTicker
{
  public:
    BpmTicker(int bpm, int beatResolution, int precisionTime, fptr callback);
    ~BpmTicker(); // destructor
    
    void doTheThing();
    void setBPM(int bpm);
    unsigned long getTickCount();
    unsigned long getTimeOfNextTick();
    unsigned long getTimeSinceLastTick();
    long getTimeToNextTick();
    void startTicking();
    void stopTicking();
    
  private:
    int bpm;
    int beatResolution;
    int precisionTime;
    fptr callback;

    bool isTicking;
    float tickCount;
    float tickDuration;
    unsigned long lastTickStamp;
    unsigned long nextTickStamp;
    void reset();
};

#endif
