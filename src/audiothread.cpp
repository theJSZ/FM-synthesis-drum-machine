#include "audiothread.h"

AudioThread::AudioThread() :
  bpm(120),
  sequencer(new Sequencer(this)),
  osc(new FMOsc)
  {}

AudioThread::~AudioThread() {
  ;
}

float AudioThread::getBpm() {
  return bpm;
}

unsigned int AudioThread::getSampleRate() {
  return sampleRate;
}

int AudioThread::audioCallback(void *outputBuffer, void *inputBuffer,
  unsigned int nBufferFrames, double streamTime,
  RtAudioStreamStatus status, void *userData)
{
  AudioThread *audioThread = static_cast<AudioThread*>(userData);
  float *buffer = (float *) outputBuffer;

  // timing stuff
  static int sampleCounter = 0;
  float bpm = audioThread->getBpm();
  float samplesPer16thNote = (SAMPLERATE * 60.0) / (bpm * 4.0);

  // audioThread->feg->setValue(1);
  // audioThread->feg->setTarget(0);
  for (unsigned int i = 0; i < nBufferFrames; ++i) {
    // processing
    sampleCounter++;
    buffer[i] = audioThread->osc->tick();
    buffer[i] *= audioThread->ampEnvelope->tick();
    double L = 0.5;
    buffer[i] = L * (tanh(buffer[i])/L);
    buffer[i] = L * (tanh(buffer[i])/L);

    // sequencer
    if (sampleCounter >= samplesPer16thNote) {
      sampleCounter = 0;
      audioThread->sequencer->advance();
    }
  }
  return 0;
}

void AudioThread::run() {
  if (audio.getDeviceCount() < 1) {
    std::cout << "No audio devices found" << std::endl;
    return;
  }

  parameters.deviceId = audio.getDefaultOutputDevice();
  parameters.nChannels = 1;

  try {
    audio.openStream(&parameters, nullptr, RTAUDIO_FLOAT32, sampleRate, &bufferFrames, &audioCallback, this);
    audio.startStream();
  }
  catch (stk::StkError & ) {
    exit(1);
  }

  exec();
}