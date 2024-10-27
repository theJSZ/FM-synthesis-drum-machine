#include "pattern.h"

Pattern::Pattern() {
  for (int i = 0; i < sizeof(patternParameters) / sizeof(patternParameters[0]) - 32; ++i) {
    patternParameters[i] = 1;
  }

  for (int i = sizeof(patternParameters) / sizeof(patternParameters[0]) - 32; i < sizeof(patternParameters) / sizeof(patternParameters[0]); ++i) {
    patternParameters[i] = 0;
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

