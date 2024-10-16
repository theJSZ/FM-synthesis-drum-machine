#include "sequencer.h"

Sequencer::Sequencer(AudioThread* audioThread) :
  audiothread(audioThread),
  currentStep(0),
  bpm(120)

  {}

Sequencer::~Sequencer() {}

void Sequencer::advance() {
  currentStep++;
  currentStep %= 16;

  emit currentStepChanged(currentStep);

}

int Sequencer::getCurrentStep() {
  return currentStep;
}
