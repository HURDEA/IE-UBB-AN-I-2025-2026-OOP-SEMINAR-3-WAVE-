/**
 * @file Wave.h
 * @brief Declarations of the AcousticWave hierarchy and utility classes.
 */

#pragma once
#include "DynamicArray.h"
#include <string>
#include <iostream>

 /**
  * @class AcousticWave
  * @brief Base class representing a generic acoustic waveform.
  */
class AcousticWave {
protected:
    float frequency;             /**< The frequency of the wave in Hertz. */
    float amplitude;             /**< The amplitude (volume) of the wave. */
    float sample_rate;           /**< The sampling rate in Hertz. */
    DynamicArray<float> samples; /**< The container storing the generated audio samples. */
    std::string wave_type;       /**< A string identifier for the type of the wave. */

public:
    /**
     * @brief Constructs an AcousticWave with specified parameters.
     * @param freq The frequency in Hertz (default 440.0f).
     * @param amp The amplitude (default 0.8f).
     * @param sr The sample rate in Hertz (default 44100.0f).
     * @param type The string representation of the wave type.
     */
    AcousticWave(float freq = 440.0f, float amp = 0.8f, float sr = 44100.0f, std::string type = "Generic");

    /**
     * @brief Virtual destructor for proper derived class cleanup.
     */
    virtual ~AcousticWave() = default;

    /**
     * @brief Allocates and initializes the sample array based on duration.
     * @param duration The length of the wave in seconds.
     */
    virtual void computeSamples(float duration);

    /**
     * @brief Retrieves the generated audio samples.
     * @return A constant reference to the underlying DynamicArray of float samples.
     */
    const DynamicArray<float>& getSamples() const;

    /**
     * @brief Retrieves the total number of allocated samples.
     * @return The integer count of samples.
     */
    int getSampleCount() const;

    /**
     * @brief Performs amplitude modulation by multiplying with another wave in-place.
     * @param other The modulating wave.
     * @return A reference to the modified current wave.
     */
    AcousticWave& operator*=(const AcousticWave& other);

    /**
     * @brief Performs amplitude modulation, returning a new wave instance.
     * @param other The modulating wave.
     * @return A newly constructed wave representing the modulation result.
     */
    AcousticWave operator*(const AcousticWave& other) const;

    /**
     * @brief Overloads the stream insertion operator for outputting wave metadata.
     * @param os The output stream.
     * @param wave The AcousticWave instance.
     * @return A reference to the modified output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const AcousticWave& wave);

    AcousticWave operator+(const AcousticWave& other) const;
};

/**
 * @class SineWave
 * @brief Derived class representing a sinusoidal waveform.
 */
class SineWave : public AcousticWave {
public:
    /**
     * @brief Constructs a SineWave.
     * @param freq The frequency in Hertz.
     * @param amp The amplitude.
     * @param sr The sample rate in Hertz.
     */
    SineWave(float freq, float amp, float sr);

    /**
     * @brief Computes the sine wave samples over a given duration.
     * @param duration The length of the wave in seconds.
     */
    void computeSamples(float duration) override;
};

/**
 * @class SquareWave
 * @brief Derived class representing a square waveform.
 */
class SquareWave : public AcousticWave {
private:
    /**
     * @brief Helper function to compute the sign of a floating-point value.
     * @param val The input value.
     * @return 1.0f if positive, -1.0f if negative, 0.0f if zero.
     */
    float sign(float val) const;

public:
    /**
     * @brief Constructs a SquareWave.
     * @param freq The frequency in Hertz.
     * @param amp The amplitude.
     * @param sr The sample rate in Hertz.
     */
    SquareWave(float freq, float amp, float sr);

    /**
     * @brief Computes the square wave samples over a given duration.
     * @param duration The length of the wave in seconds.
     */
    void computeSamples(float duration) override;
};

/**
 * @class TriangleWave
 * @brief Derived class representing a triangle waveform.
 */
class TriangleWave : public AcousticWave {
public:
    /**
     * @brief Constructs a TriangleWave.
     * @param freq The frequency in Hertz.
     * @param amp The amplitude.
     * @param sr The sample rate in Hertz.
     */
    TriangleWave(float freq, float amp, float sr);

    /**
     * @brief Computes the triangle wave samples over a given duration.
     * @param duration The length of the wave in seconds.
     */
    void computeSamples(float duration) override;
};

/**
 * @class SawtoothWave
 * @brief Derived class representing a sawtooth waveform.
 */
class SawtoothWave : public AcousticWave {
public:
    /**
     * @brief Constructs a SawtoothWave.
     * @param freq The frequency in Hertz.
     * @param amp The amplitude.
     * @param sr The sample rate in Hertz.
     */
    SawtoothWave(float freq, float amp, float sr);

    /**
     * @brief Computes the sawtooth wave samples over a given duration.
     * @param duration The length of the wave in seconds.
     */
    void computeSamples(float duration) override;
};

/**
 * @class SynthesizerTrack
 * @brief Derived class representing a sequential track of multiple acoustic waveforms.
 */
class SynthesizerTrack : public AcousticWave {
public:
    /**
     * @brief Constructs a SynthesizerTrack.
     * @param sr The sample rate in Hertz (default 44100.0f).
     */
    SynthesizerTrack(float sr = 44100.0f);

    /**
     * @brief Generates and appends a note's samples to the track.
     * @param freq The frequency in Hertz.
     * @param duration The duration of the note in seconds.
     * @param amp The amplitude of the note.
     */
    void addNote(float freq, float duration, float amp = 0.5f);
};

/**
 * @class WaveOutput
 * @brief Utility class for file operations related to acoustic waves.
 */
class WaveOutput {
public:
    /**
     * @brief Saves the samples of an AcousticWave to a specified file path in CSV format.
     * @param csv_path The destination file path.
     * @param w The AcousticWave instance to serialize.
     * @return True if the operation succeeded, false otherwise.
     */
    static bool saveSamples(const std::string& csv_path, const AcousticWave& w);
};