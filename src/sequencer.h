#ifndef SEQUENCER_H
#define SEQUENCER_H

#include "math.h"
#include <QObject>
#include <QKeyEvent>

#include "sequencerStep.h"
#include "audiothread.h"
#include "mainwindow.h"
#include "pattern.h"

class MainWindow;
class AudioThread;

class Sequencer : public QObject {
  Q_OBJECT
public:
  Sequencer(AudioThread* audioThread, MainWindow *mainWindow);
  ~Sequencer();
  void advance();
  int getCurrentStepNumber();
  SequencerStep *steps[32];
  void toggleActiveStep(int step);
  bool activeStep[32] = {0};
  Pattern *patterns[8];

// public slots:
//   void onKeyPressed(QKeyEvent *event);

signals:
  void currentStepChanged(int newStepNumber);
  void stepActiveStatusChanged(int stepNumber, bool on);

private:
  int bpm = 120;
  AudioThread *audiothread;
  MainWindow *mainWindow;
  int currentStepNumber = 0;
  void updateOsc(int step);
  void playStep(int step);
  // void shiftPattern(int shiftAmount);
  // int patternShiftAmount;
};

#endif