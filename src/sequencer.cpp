#include "sequencer.h"

Sequencer::Sequencer(AudioThread* audioThread) :
  audiothread(audioThread),
  currentStepNumber(0),
  bpm(120),
  activeStep{0}

  {
    for (int i = 0; i < 8; ++i) {
      steps[i] = new SequencerStep;
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
  currentStepNumber %= 32;
  emit currentStepChanged(currentStepNumber);

  bool playStep = activeStep[currentStepNumber];
  if (rand() % 100 < steps[currentStepNumber % 8]->randomness) {
    playStep = !playStep;
  }

  // trig envelopes
  if (playStep) {
    audiothread->voices->voices[currentStepNumber % 8]->ampEnvelope->setValue(1.0);
    audiothread->voices->voices[currentStepNumber % 8]->ampEnvelope->setTarget(0.0);
    audiothread->voices->voices[currentStepNumber % 8]->pitchEnvelope->setValue(1.0);
    audiothread->voices->voices[currentStepNumber % 8]->pitchEnvelope->setTarget(0.0);
    audiothread->voices->voices[currentStepNumber % 8]->fmEnvelope->setValue(1.0);
    audiothread->voices->voices[currentStepNumber % 8]->fmEnvelope->setTarget(0.0);
    // set oscillator
    updateOsc(currentStepNumber % 8);
  }

}

int Sequencer::getCurrentStepNumber() {
  return currentStepNumber;
}

void Sequencer::updateOsc(int stepNumber) {
  FMOsc *osc = audiothread->voices->voices[stepNumber];
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