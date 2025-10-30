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

  float frequencyMultiplier = 1;
  float rampAmount = 0;
  float rampDecay = 0.001;

  float fmAmount = 0;
  float fmFrequencyMultiplier = 1;
  float fmDecay = 0.001;
  float fmFeedback = 0.0;

  float aegDecay = 0.001;
  float volume = 1;

  float masterFrequencyMultiplier = 1;
  float previousModulatorSample;
  float currentModulatorSample;


};

#endif