#ifndef SEQUENCERSTEP_H
#define SEQUENCERSTEP_H

#include "constants.h"

class SequencerStep {
public:
  SequencerStep() :
    frequency(BASE_FREQUENCY),
    rampAmount(0.0),
    rampDecay(0.0),

    fmAmount(0.0),
    fmFrequency(BASE_FM_FREQUENCY),
    fmDecay(0.0),
    fmFeedback(0.0),

    aegDecay(BASE_AEG_DECAY),
    volume(1.0)
  {}

  ~SequencerStep() {}

  float frequency;
  float rampAmount;
  float rampDecay;

  float fmAmount;
  float fmFrequency;
  float fmDecay;
  float fmFeedback;

  float aegDecay;
  float volume;
};

#endif