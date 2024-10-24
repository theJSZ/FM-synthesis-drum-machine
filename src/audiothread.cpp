#include "audiothread.h"

AudioThread::AudioThread() :
  bpm(160),
  sequencer(new Sequencer(this)),
  voices(new EightVoices()),
  reverb(new stk::FreeVerb()),
  reverbMix(0.5),
  masterVolume(1.0)
  {
  }

AudioThread::~AudioThread() {
}

float AudioThread::getBpm() {
  return (float) this->bpm;
}

void AudioThread::setBpm(float bpm) {
  this->bpm = bpm;
  std::cout << "BPM: " << this->bpm << std::endl;
}

unsigned int AudioThread::getSampleRate() {
  return sampleRate;
}

void AudioThread::setReverbMix(float mix) {
  // reverbMix = mix;
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

  // this will be useful when swing is implemented
  static int evenstep = 1;

  for (unsigned int i = 0; i < nBufferFrames; ++i) {
    sampleCounter++;
    buffer[i] = audioThread->voices->tick();

    buffer[i] = audioThread->reverb->tick(buffer[i], 0);
    double L = 0.5;
    buffer[i] = L * (tanh(buffer[i])/L);
    buffer[i] = L * (tanh(buffer[i])/L);
    buffer[i] *= audioThread->masterVolume;

    // // sequencer
    if (sampleCounter >= samplesPer16thNote + evenstep * (((float) audioThread->swing / 1000) * samplesPer16thNote)) {
      sampleCounter = 0;
      evenstep *= -1;
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
    std::cout << "audio stream started" << std::endl;
  }
  catch (stk::StkError & ) {
    std::cout << "could not start audio stream" << std::endl;
    exit(1);
  }
}