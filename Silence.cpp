#include "Silence.h"

Silence::Silence(float sr)
    : AcousticWave(0.0f, 0.0f, sr, "Silence") {
}

void Silence::computeSamples(float duration) {
    // The base class implementation already resizes and fills with 0.0f
    AcousticWave::computeSamples(duration);
}