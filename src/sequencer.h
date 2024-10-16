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
  int getCurrentStep();
  SequencerStep *steps[16];

signals:
  void currentStepChanged(int newStep);

private:
  int bpm;
  AudioThread* audiothread;
  int currentStep;
};

#endif