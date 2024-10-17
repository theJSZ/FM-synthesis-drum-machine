#include "fmosc.h"

FMOsc::FMOsc() :
  carrier(new stk::SineWave),
  modulator(new stk::SineWave),
  frequency(400.0),
  rampAmount(0.0),
  rampDecay(0.001),
  fmAmount(0.0),
  fmFrequencyMultiplier(1.0),
  fmDecay(0.001),
  fmFeedback(0.0),
  aegDecay(0.001),
  volume(1.0)

  {
    std::cout << "oscillator created" << std::endl;
  }
FMOsc::~FMOsc() {}

void FMOsc::setFrequency(float frequency) {
  carrier->setFrequency(frequency);
  this->frequency = frequency;
  modulator->setFrequency(fmFrequencyMultiplier * frequency);
}

void FMOsc::setRampAmount(float rampAmount) {
  this->rampAmount = rampAmount;
}

void FMOsc::setRampDecay(float rampDecay) {
  this->rampDecay = rampDecay;
}

void FMOsc::setFmAmount(float fmAmount) {
  this->fmAmount = fmAmount;
}

void FMOsc::setFmFrequencyMultiplier(float fmFrequencyMultiplier) {
  this->fmFrequencyMultiplier = fmFrequencyMultiplier;
}

void FMOsc::setFmDecay(float fmDecay) {
  this->fmDecay = fmDecay;
}

void FMOsc::setFmFeedback(float fmFeedback) {
  this->fmFeedback = fmFeedback;
}

void FMOsc::setAegDecay(float aegDecay) {
  this->aegDecay = aegDecay;
}

void FMOsc::setVolume(float volume) {
  this->volume = volume;
}

void FMOsc::reset() {
  carrier->reset();
}

float FMOsc::tick() {
  double mod_tick = modulator->tick();
  modulator->addPhase(mod_tick * fmFeedback);
  carrier->addPhase(mod_tick * fmAmount);
  return carrier->tick() * this->volume;
}

