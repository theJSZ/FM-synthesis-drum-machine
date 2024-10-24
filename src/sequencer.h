#ifndef SEQUENCER_H
#define SEQUENCER_H

#include "math.h"
#include "sequencerStep.h"
#include "audiothread.h"
#include <QObject>

class AudioThread;

class Sequencer : public QObject {
  Q_OBJECT
public:
  Sequencer(AudioThread* audioThread);
  ~Sequencer();
  void advance();
  int getCurrentStepNumber();
  SequencerStep *steps[32];
  void toggleActiveStep(int step);
  bool activeStep[32];

signals:
  void currentStepChanged(int newStepNumber);
  void stepActiveStatusChanged(int stepNumber, bool on);

private:
  int bpm;
  AudioThread* audiothread;
  int currentStepNumber;
  void updateOsc(int step);
  void playStep(int step);
};

#endif