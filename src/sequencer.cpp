#include "sequencer.h"

Sequencer::Sequencer(AudioThread* audioThread) :
  audiothread(audioThread),
  currentStep(0),
  bpm(120)

  {
    for (int i = 0; i < 16; ++i) {
      steps[i] = new SequencerStep;
      std::cout << i << std::endl;
    }
    std::cout << "sequencer created" << std::endl;
  }

Sequencer::~Sequencer() {}

void Sequencer::advance() {
  currentStep++;
  currentStep %= 16;
  std::cout << "step " << currentStep << std::endl;
  audiothread->ampEnvelope->setValue(1.0);
  audiothread->ampEnvelope->setTarget(0.0);
  audiothread->osc->setFrequency(steps[currentStep]->frequency);
}

int Sequencer::getCurrentStep() {
  return currentStep;
}
