#pragma once
#include "Wave.h"

/**
 * @class SignalProcessor
 * @brief Utility class for applying digital signal processing effects.
 */
class SignalProcessor {
public:
    /**
     * @brief Applies an echo effect to an AcousticWave in-place.
     * @param wave The wave to modify.
     * @param delay The delay of the echo in seconds.
     * @param attenuation The volume reduction factor for the echo (0 < a < 1).
     */
    static void applyEcho(AcousticWave& wave, float delay, float attenuation);
};