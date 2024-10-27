#include "fmosc.h"

FMOsc::FMOsc() :
  carrier(new stk::SineWave()),
  modulator(new stk::SineWave()),
  ampEnvelope(new stk::ADSR()),
  ampEnvelope2(new stk::ADSR()),
  fmEnvelope(new stk::ADSR()),
  pitchEnvelope(new stk::ADSR())
  {
    ampEnvelope->setAllTimes(0.001, 1, 0.0, 0.001);
    ampEnvelope2->setAllTimes(0.01, 0.01, 0.0, 0.001);
    fmEnvelope->setAllTimes(0.001, 1, 0.0, 0.001);
    ampEnvelope->setAllTimes(0.001, 1, 0.0, 0.001);
  }
FMOsc::~FMOsc() {
  delete carrier;
  delete modulator;
  delete ampEnvelope;
  delete ampEnvelope2;
  delete fmEnvelope;
  delete pitchEnvelope;
}

void FMOsc::setFrequencyMultiplier(float frequencyMultiplier) {
  this->frequencyMultiplier = frequencyMultiplier;
}

void FMOsc::setRampAmount(float rampAmount) {
  this->rampAmount = rampAmount;
}

void FMOsc::setRampDecay(float rampDecay) {
  pitchEnvelope->setDecayTime(rampDecay);
}

void FMOsc::setFmAmount(float fmAmount) {
  this->fmAmount = fmAmount;
}

void FMOsc::setFmFrequencyMultiplier(float fmFrequencyMultiplier) {
  this->fmFrequencyMultiplier = fmFrequencyMultiplier;
}

void FMOsc::setFmDecay(float fmDecay) {
  fmEnvelope->setDecayTime(fmDecay);
}

void FMOsc::setFmFeedback(float fmFeedback) {
  this->fmFeedback = fmFeedback;
}

void FMOsc::setAegDecay(float aegDecay) {
  ampEnvelope->setDecayTime(aegDecay);
}

void FMOsc::setVolume(float volume) {
  this->volume = volume;
}

void FMOsc::setMasterFrequencyMultiplier(float frequencyMultiplier) {
  this->masterFrequencyMultiplier = frequencyMultiplier;
}

void FMOsc::reset() {
  carrier->reset();
  modulator->reset();
}

float FMOsc::tick() {
  float targetVolume = volume * ampEnvelope->tick();
  ampEnvelope2->setTarget(targetVolume);
  float targetFrequency = (BASE_FREQUENCY * frequencyMultiplier * masterFrequencyMultiplier) * (1 + (4* rampAmount * pitchEnvelope->tick()));
  carrier->setFrequency(targetFrequency);
  modulator->setFrequency(targetFrequency * fmFrequencyMultiplier);
  double modTick = modulator->tick() * fmEnvelope->tick();
  modulator->addPhase(modTick * fmFeedback);
  carrier->addPhase(modTick * fmAmount);
  return carrier->tick() *  ampEnvelope2->tick();
}

