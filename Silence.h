#pragma once
#include "Wave.h"

/**
 * @class Silence
 * @brief Represents a pause or gap in transmission (all zero samples).
 */
class Silence : public AcousticWave {
public:
    /**
     * @brief Constructs a Silence wave.
     * @param sr The sample rate in Hertz (default 44100.0f).
     */
    Silence(float sr = 44100.0f);

    /**
     * @brief Generates silent samples for the given duration.
     * @param duration The length of the silence in seconds.
     */
    void computeSamples(float duration) override;
};