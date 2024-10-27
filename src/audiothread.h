#ifndef AUDIOTHREAD_H
#define AUDIOTHREAD_H

#include <stdio.h>
#include <memory>

#include <QThread>

#include <RtAudio.h>
#include <Stk.h>
#include <ADSR.h>
#include <FreeVerb.h>

#include <SDL2/SDL.h>

#include "sequencer.h"
#include "fmosc.h"
#include "constants.h"
#include "eightVoices.h"
#include "mainwindow.h"

class Sequencer;
class MainWindow;
class AudioThread : public QThread {
	Q_OBJECT
public:
	AudioThread(MainWindow *mainWindow, QObject *parent = nullptr);
	~AudioThread();
	EightVoices *voices;

	unsigned int getSampleRate();
	float getBpm();
	Sequencer *sequencer;

	void setBpm(float bpm);
	void setReverbMix(float mix);
	void setReverbDamp(float damp);
	void setReverbRoomSize(float damp);

	void setMasterVolume(float volume);
	void setSwing(int swing);

protected:
	void run() override;

private:
	static int audioCallback(
		void *outputBuffer, void *inputBuffer,
		unsigned int nBufferFrames, double streamTime,
		RtAudioStreamStatus status, void *userData);

	RtAudio audio;
	RtAudio::StreamParameters parameters;
	unsigned int sampleRate = SAMPLERATE;
	unsigned int bufferFrames = BUFFER_FRAMES;
	float bpm = 160;
	int swing = 0;

	stk::FreeVerb *reverb;
	float reverbMix = 0.5;
	float masterVolume = 1;

};

#endif