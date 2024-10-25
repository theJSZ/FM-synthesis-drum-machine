#include "pattern.h"

Pattern::Pattern() {
  for (int i = 0; i < sizeof(patternParameters) / sizeof(patternParameters[0]); ++i) {
    patternParameters[i] = 1;
  }
}

int *Pattern::getPatternParameters() {
  return patternParameters;
}

void Pattern::setPatternParameters(int *parameters) {
  for (int i = 0; i < sizeof(patternParameters) / sizeof(patternParameters[0]); ++i) {
    patternParameters[i] = parameters[i];
  }
}

