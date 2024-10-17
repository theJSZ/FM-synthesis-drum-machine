#include "audiothread.h"

AudioThread::AudioThread() :
  bpm(120),
  sequencer(new Sequencer(this)),
  osc(new FMOsc),
  ampEnvelope(new stk::ADSR),
  fmEnvelope(new stk::ADSR)
  {
    ampEnvelope->setAllTimes(0.001, 1, 0.0, 0.001);
    osc->setVolume(1.0);
    osc->setFmAmount(0.0);
    osc->setFrequency(200.0);
  }

AudioThread::~AudioThread() {

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
  static float bpm = audioThread->getBpm();
  static float samplesPer16thNote = (SAMPLERATE * 60.0) / (bpm * 4.0);

  for (unsigned int i = 0; i < nBufferFrames; ++i) {
    buffer[i] = audioThread->osc->tick();

    // // processing
    sampleCounter++;
    buffer[i] = audioThread->osc->tick() * audioThread->ampEnvelope->tick();
    double L = 0.5;
    buffer[i] = L * (tanh(buffer[i])/L);
    buffer[i] = L * (tanh(buffer[i])/L);

    // // sequencer
    if (sampleCounter >= samplesPer16thNote) {
      // std::cout << "next step!" << std::endl;
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
    std::cout << "audio stream started" << std::endl;
  }
  catch (stk::StkError & ) {
    std::cout << "could not start audio stream" << std::endl;
    exit(1);
  }

  // try {
  //   exec();
  // } catch (std::exception& e) {
  //   std::cerr << "Exception caught: " << e.what() << std::endl;
  // } catch (...) {
  //   std::cerr << "Unknown exception caught" << std::endl;
  // }
  // exec();
}