#ifndef FMOSC_H
#define FMOSC_H

#include "SineWave.h"

class FMOsc {
public:
  FMOsc();
  ~FMOsc();

  void setFrequency(float frequency);
  void setRampAmount(float rampAmount);
  void setRampDecay(float rampDecay);
  void setFmAmount(float fmAmount);
  void setFmFrequencyMultiplier(float fmFrequency);
  void setFmDecay(float fmDecay);
  void setFmFeedback(float fmFeedback);
  void setAegDecay(float aegDecay);
  void setVolume(float volume);

  void reset();
  float tick();

private:

  stk::SineWave *carrier;
  stk::SineWave *modulator;

  float frequency;
  float rampAmount;
  float rampDecay;

  float fmAmount;
  float fmFrequencyMultiplier;
  float fmDecay;
  float fmFeedback;

  float aegDecay;
  float volume;
};

#endif