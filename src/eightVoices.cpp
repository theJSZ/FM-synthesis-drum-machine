#include "eightVoices.h"

EightVoices::EightVoices() {
    for (int i = 0; i < 8; ++i) {
        voices[i] = new FMOsc();
        std::cout << "created FMOsc" << i << std::endl;
    }
}

double EightVoices::tick() {
    double outputSample = 0;
    for (auto voice : voices) {
        outputSample += voice->tick();
    }
    return outputSample;
}