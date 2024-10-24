#ifndef AUDIOTHREAD_H
#define AUDIOTHREAD_H

#include <stdio.h>

#include <QThread>

#include <RtAudio.h>
#include <Stk.h>
#include <ADSR.h>
#include <FreeVerb.h>

#include "sequencer.h"
#include "fmosc.h"
#include "constants.h"
#include "eightVoices.h"

class Sequencer;
class AudioThread : public QThread {
public:
	AudioThread();
	~AudioThread();
	// FMOsc *osc;
	EightVoices *voices;


	// stk::ADSR *fmEnvelope;
	// stk::ADSR *ampEnvelope;

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
	float bpm;
	int swing;

	stk::FreeVerb *reverb;
	float reverbMix;
	float masterVolume;
};

#endif