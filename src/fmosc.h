#ifndef FMOSC_H
#define FMOSC_H

#include <SineWave.h>
#include "constants.h"
#include <ADSR.h>

class FMOsc {
public:
  FMOsc();
  ~FMOsc();

  void setFrequencyMultiplier(float frequencyMultiplier);
  void setRampAmount(float rampAmount);
  void setRampDecay(float rampDecay);
  void setFmAmount(float fmAmount);
  void setFmFrequencyMultiplier(float fmFrequencyMultiplier);
  void setFmDecay(float fmDecay);
  void setFmFeedback(float fmFeedback);
  void setAegDecay(float aegDecay);
  void setVolume(float volume);

  void setMasterFrequencyMultiplier(float frquencyMultiplier);

  void reset();
  float tick();

  stk::ADSR *fmEnvelope;
	stk::ADSR *ampEnvelope;
	stk::ADSR *ampEnvelope2;
  stk::ADSR *pitchEnvelope;


private:

  stk::SineWave *carrier;
  stk::SineWave *modulator;

  float frequencyMultiplier;
  float rampAmount;
  float rampDecay;

  float fmAmount;
  float fmFrequencyMultiplier;
  float fmDecay;
  float fmFeedback;

  float aegDecay;
  float volume;

  float masterFrequencyMultiplier;


};

#endif