#include "fmosc.h"

FMOsc::FMOsc() {}
FMOsc::~FMOsc() {}

void FMOsc::setFrequency(float frequency) {
  carrier.setFrequency(frequency);
  this->frequency = frequency;
  modulator.setFrequency(fmFrequencyMultiplier * frequency);
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
  carrier.reset();
}

float FMOsc::tick() {
  double mod_tick = modulator.tick();
  modulator.addPhase(mod_tick * fmFeedback);
  carrier.addPhase(mod_tick * fmAmount);
  return carrier.tick() * this->volume;
}

