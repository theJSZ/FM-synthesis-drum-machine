#ifndef EIGHTVOICES_H
#define EIGHTVOICES_H

#include "fmosc.h"

class EightVoices {
public:
    EightVoices();
    ~EightVoices();
    double tick();
    FMOsc *voices[8];
private:
};

#endif