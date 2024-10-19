#include "sequencer.h"

Sequencer::Sequencer(AudioThread* audioThread) :
  audiothread(audioThread),
  currentStepNumber(0),
  bpm(120),
  activeStep{0}

  {
    for (int i = 0; i < 16; ++i) {
      steps[i] = new SequencerStep;
      std::cout << i << std::endl;
    }
    std::cout << "sequencer created" << std::endl;
  }

Sequencer::~Sequencer() {}

void Sequencer::toggleActiveStep(int step) {
  activeStep[step] = !activeStep[step];
  emit stepActiveStatusChanged(step, activeStep[step]);
}

void Sequencer::advance() {
  currentStepNumber++;
  currentStepNumber %= 16;
  emit currentStepChanged(currentStepNumber);

  // trig envelopes
  if (activeStep[currentStepNumber]) {
    audiothread->osc->ampEnvelope->setValue(1.0);
    audiothread->osc->ampEnvelope->setTarget(0.0);
    audiothread->osc->pitchEnvelope->setValue(1.0);
    audiothread->osc->pitchEnvelope->setTarget(0.0);
    audiothread->osc->fmEnvelope->setValue(1.0);
    audiothread->osc->fmEnvelope->setTarget(0.0);
    // set oscillator
    updateOsc(currentStepNumber % 8);
  }

}

int Sequencer::getCurrentStepNumber() {
  return currentStepNumber;
}

void Sequencer::updateOsc(int stepNumber) {
  FMOsc *osc = audiothread->osc;
  SequencerStep *step = steps[stepNumber];

  osc->setFrequencyMultiplier(step->frequencyMultiplier);
  osc->setRampAmount(step->rampAmount);
  osc->setRampDecay(step->rampDecay);

  osc->setFmAmount(step->fmAmount);
  osc->setFmFrequencyMultiplier(step->fmFrequencyMultiplier);
  osc->setFmDecay(step->fmDecay);
  osc->setFmFeedback(step->fmFeedback);

  osc->setAegDecay(step->aegDecay);
  osc->setVolume(step->volume);
}