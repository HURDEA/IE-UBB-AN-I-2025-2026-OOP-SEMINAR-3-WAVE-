#include "SignalProcessor.h"

void SignalProcessor::applyEcho(AcousticWave& wave, float delay, float attenuation) {
    // We assume the standard 44100.0f sample rate here. 
    // If you want it completely dynamic, add a getSampleRate() getter to AcousticWave.
    float sampleRate = 44100.0f;
    int delaySamples = static_cast<int>(delay * sampleRate);

    // We loop backwards to avoid compounding the echo on itself. 
    // If we looped forwards, the modified sample 'i' would become the "pastSample" for a future calculation.
    for (int i = wave.getSampleCount() - 1; i >= delaySamples; --i) {

        float currentSample = wave.getSample(i);
        float pastSample = wave.getSample(i - delaySamples);

        // Apply the formula: new = current + (past * attenuation)
        wave.setSample(i, currentSample + (pastSample * attenuation));
    }
}