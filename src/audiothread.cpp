#include "audiothread.h"

AudioThread::AudioThread(MainWindow *mainWindow, QObject *parent) :
  QThread(parent),
  sequencer(new Sequencer(this, mainWindow)),
  voices(new EightVoices()),
  reverb(new stk::FreeVerb())
  {
  }

AudioThread::~AudioThread() {
  delete sequencer;
  delete voices;
  delete reverb;
}

int AudioThread::audioCallback(void *outputBuffer, void *inputBuffer,
  unsigned int nBufferFrames, double streamTime,
  RtAudioStreamStatus status, void *userData)
{

  AudioThread *audioThread = static_cast<AudioThread*>(userData);
  float *buffer = (float *) outputBuffer;

  // count samples to know when to advance sequencer
  static int sampleCounter = 0;
  float bpm = audioThread->getBpm();
  float samplesPer16thNote = (SAMPLERATE * 60.0) / (bpm * 4.0);

  // for swing purposes
  static int evenstep = 1;

  for (unsigned int i = 0; i < nBufferFrames; ++i) {
    sampleCounter++;

    // get raw audio
    buffer[i] = audioThread->voices->tick() * audioThread->masterVolume;

    // apply reverb
    buffer[i] = audioThread->reverb->tick(buffer[i], 0);

    // apply waveshaping
    double L = 0.5;
    buffer[i] = L * (tanh(buffer[i])/L);
    buffer[i] = L * (tanh(buffer[i])/L);

    // advance sequencer
    if (sampleCounter >= samplesPer16thNote + evenstep * (((float) audioThread->swing / 1000) * samplesPer16thNote)) {
      sampleCounter = 0;
      evenstep *= -1;
      audioThread->sequencer->advance();
    }
  }
  return 0;
}

float AudioThread::getBpm() {
  return (float) this->bpm;
}

void AudioThread::setBpm(float bpm) {
  this->bpm = bpm;
}

unsigned int AudioThread::getSampleRate() {
  return sampleRate;
}

void AudioThread::setReverbMix(float mix) {
  reverb->setEffectMix(mix);
}

void AudioThread::setReverbDamp(float damp) {
  reverb->setDamping(damp);
}

void AudioThread::setReverbRoomSize(float size) {
  reverb->setRoomSize(size);
}

void AudioThread::setMasterVolume(float volume) {
  masterVolume = volume*volume;
}

void AudioThread::setSwing(int swing) {
  this->swing = swing;
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
    std::cout << "audio stream started" << std::endl;
  }
  catch (stk::StkError & ) {
    std::cout << "could not start audio stream" << std::endl;
    exit(1);
  }
}