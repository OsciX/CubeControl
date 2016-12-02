/*
CubeControl.h - Library for controlling an LED cube
Created by Ryan Davis, December 1, 2016
*/
#ifndef CubeControl_h
#define CubeControl_h
#include "Arduino.h"

class LedCube
{
  public:
    LedCube();
    const unsigned char columnPinmap[7][7];
    const unsigned char layerPins[7][7];
    void SingleLedPWM(int coordX, int coordY, int coordZ, unsigned int millisOn = 1, char dutyCyclePercent = 50);
    void SingleLedPWM_Fallback(int coordX, int coordY, int coordZ, unsigned int millisOn = 1, char dutyCyclePercent = 50);
  private:
    unsigned int _millisOff;
    unsigned long _initialMillis;
    unsigned long _currentMillis;
    bool _delayPassed;
};

#endif
