#include "Arduino.h"
#include "CubeControl.h"

LedCube::LedCube() {}

const unsigned char columnPinmap[7][7] = {
{48, 68, 41, 61, 34, 27, 20},
{47, 67, 40, 60, 33, 26, 19},
{46, 66, 39, 59, 32, 25, 18},
{45, 65, 38, 58, 31, 24, 17},
{44, 64, 37, 57, 30, 23, 16},
{43, 63, 36, 56, 29, 22, 15},
{42, 62, 35, 55, 28, 21, 14},
};

const unsigned char layerPins[7] = {2, 3, 4, 5, 6, 7, 8};

void LedCube::SingleLedPWM(int coordX, int coordY, int coordZ, unsigned int millisOn, char dutyCyclePercent) {
  unsigned int _millisOff = 100 / dutyCyclePercent * millisOn - millisOn;
  unsigned long _initialMillis = millis();
  bool _delayPassed = false;

  coordX--;
  coordY--;
  coordZ--;

  pinMode(columnPinmap[coordX-1][coordY-1], OUTPUT);
  pinMode(layerPins[coordZ-1], OUTPUT);
  digitalWrite(columnPinmap[coordX][coordY], HIGH);
  digitalWrite(layerPins[coordZ], LOW);

  while (_delayPassed == false) {
    unsigned long _currentMillis = millis();
    if (millisOn >= _currentMillis - _initialMillis){
      digitalWrite(columnPinmap[coordX][coordY], LOW);
      _delayPassed = true;
    }
  }

  _delayPassed = false;
  _initialMillis = millis();
  while (_delayPassed == false) {
    _currentMillis = millis();
    if (_millisOff >= _currentMillis - _initialMillis){
      _delayPassed = true; 
    }
  }
  
}

void LedCube::SingleLedPWM_Fallback(int coordX, int coordY, int coordZ, unsigned int millisOn, char dutyCyclePercent) {
  unsigned int _millisOff = 100 / dutyCyclePercent * millisOn - millisOn;
  
  pinMode(columnPinmap[coordX-1][coordY-1], OUTPUT);
  pinMode(layerPins[coordZ-1], OUTPUT);
  digitalWrite(layerPins[coordZ-1], LOW);
 
  digitalWrite(columnPinmap[coordX-1][coordY-1], HIGH);
  delay(millisOn);
  digitalWrite(columnPinmap[coordX-1][coordY-1], LOW);
  delay(_millisOff);
    
}

