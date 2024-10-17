#ifndef SEQUENCERSTEP_H
#define SEQUENCERSTEP_H

#include "constants.h"

class SequencerStep {
public:
  SequencerStep() :
    frequencyMultiplier(1),
    rampAmount(0.0),
    rampDecay(0.01),

    fmAmount(0.0),
    fmFrequencyMultiplier(BASE_FM_MULTIPLIER),
    fmDecay(0.01),
    fmFeedback(0.0),

    aegDecay(BASE_AEG_DECAY),
    volume(1.0),

    active(true)
  {}

  void toggleActive() {
    active = !active;
  }

  ~SequencerStep() {}

  float frequencyMultiplier;
  float rampAmount;
  float rampDecay;

  float fmAmount;
  float fmFrequencyMultiplier;
  float fmDecay;
  float fmFeedback;

  float aegDecay;
  float volume;

  bool active;
};

#endif