#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
#include <QString>

const float BASE_FREQUENCY = 80;
const float BASE_FM_MULTIPLIER = 1;
const float BASE_AEG_DECAY = 1;
const unsigned int SAMPLERATE = 44100;
const unsigned int BUFFER_FRAMES = 512;

const int N_STEPS = 8;

// const std::string STEP_STYLESHEET_DEFAULT  = "border: 2px solid black; border-radius: 10; background-color: gray";
// const std::string STEP_STYLESHEET_CURRENT  = "border: 2px solid black; border-radius: 10; background-color: #F0C0F0";
// const std::string STEP_STYLESHEET_DISABLED = "border: 2px solid black; border-radius: 10; background-color: #404040";

const QString STEP_STYLESHEET_NON_ACTIVE = "border-radius:3; border: 1px solid black; background-color: gray";
const QString STEP_STYLESHEET_ACTIVE     = "border-radius:3; border: 1px solid black; background-color: red";
const QString STEP_STYLESHEET_CURRENT    = "border-radius:3; border: 1px solid black; background-color: white";

#endif