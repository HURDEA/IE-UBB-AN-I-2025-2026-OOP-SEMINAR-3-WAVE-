/**
 * @file Wave.cpp
 * @brief Implementation of the AcousticWave hierarchy and WaveOutput classes.
 */

#include "Wave.h"
#include <cmath>
#include <fstream>
#include <algorithm>

const float PI = std::acos(-1.0f);

AcousticWave::AcousticWave(float freq, float amp, float sr, std::string type)
    : frequency(freq), amplitude(amp), sample_rate(sr), wave_type(type) {
}

void AcousticWave::computeSamples(float duration) {
    int num_samples = static_cast<int>(duration * sample_rate);
    samples.resize(num_samples);
    for (int i = 0; i < num_samples; ++i) {
        samples[i] = 0.0f;
    }
}

const DynamicArray<float>& AcousticWave::getSamples() const {
    return samples;
}

int AcousticWave::getSampleCount() const {
    return samples.getSize();
}

AcousticWave& AcousticWave::operator*=(const AcousticWave& other) {
    int min_size = std::min(samples.getSize(), other.samples.getSize());
    for (int i = 0; i < min_size; ++i) {
        samples[i] *= other.samples[i];
    }
    wave_type += " (Modulated)";
    return *this;
}

AcousticWave AcousticWave::operator*(const AcousticWave& other) const {
    AcousticWave result(*this);
    result *= other;
    return result;
}

std::ostream& operator<<(std::ostream& os, const AcousticWave& wave) {
    os << "Wave Type: " << wave.wave_type << "\n"
        << "Frequency: " << wave.frequency << " Hz\n"
        << "Samples: " << wave.samples << "\n";
    return os;
}

SineWave::SineWave(float freq, float amp, float sr)
    : AcousticWave(freq, amp, sr, "Sine") {
}

void SineWave::computeSamples(float duration) {
    AcousticWave::computeSamples(duration);
    for (int i = 0; i < samples.getSize(); ++i) {
        float t = i / sample_rate;
        samples[i] = amplitude * std::sin(2.0f * PI * frequency * t);
    }
}

SquareWave::SquareWave(float freq, float amp, float sr)
    : AcousticWave(freq, amp, sr, "Square") {
}

float SquareWave::sign(float val) const {
    return (val > 0.0f) ? 1.0f : ((val < 0.0f) ? -1.0f : 0.0f);
}

void SquareWave::computeSamples(float duration) {
    AcousticWave::computeSamples(duration);
    for (int i = 0; i < samples.getSize(); ++i) {
        float t = i / sample_rate;
        float y_si = std::sin(2.0f * PI * frequency * t);
        samples[i] = amplitude * sign(y_si);
    }
}

TriangleWave::TriangleWave(float freq, float amp, float sr)
    : AcousticWave(freq, amp, sr, "Triangle") {
}

void TriangleWave::computeSamples(float duration) {
    AcousticWave::computeSamples(duration);
    for (int i = 0; i < samples.getSize(); ++i) {
        float t = i / sample_rate;
        samples[i] = (2.0f * amplitude / PI) * std::asin(std::sin(2.0f * PI * frequency * t));
    }
}

SawtoothWave::SawtoothWave(float freq, float amp, float sr)
    : AcousticWave(freq, amp, sr, "Sawtooth") {
}

void SawtoothWave::computeSamples(float duration) {
    AcousticWave::computeSamples(duration);
    for (int i = 0; i < samples.getSize(); ++i) {
        float t = i / sample_rate;
        float cot_val = 1.0f / std::tan(t * PI * frequency + 0.0001f);
        samples[i] = (2.0f * amplitude / PI) * std::atan(cot_val);
    }
}

SynthesizerTrack::SynthesizerTrack(float sr)
    : AcousticWave(0.0f, 0.0f, sr, "Synth Track") {
}

void SynthesizerTrack::addNote(float freq, float duration, float amp) {
    float play_duration = duration * 0.9f;
    float rest_duration = duration * 0.1f;

    if (freq > 0.0f) {
        SquareWave note(freq, amp, sample_rate);
        note.computeSamples(play_duration);
        const auto& note_samples = note.getSamples();

        int old_size = samples.getSize();
        int num_new_samples = note_samples.getSize();
        samples.resize(old_size + num_new_samples);

        for (int i = 0; i < num_new_samples; ++i) {
            samples[old_size + i] = note_samples[i];
        }
    }
    else {
        rest_duration = duration;
    }

    if (rest_duration > 0.0f) {
        int old_size = samples.getSize();
        int num_rest_samples = static_cast<int>(rest_duration * sample_rate);
        samples.resize(old_size + num_rest_samples);
        for (int i = 0; i < num_rest_samples; ++i) {
            samples[old_size + i] = 0.0f;
        }
    }
}

bool WaveOutput::saveSamples(const std::string& csv_path, const AcousticWave& w) {
    std::ofstream file(csv_path);
    if (!file.is_open()) return false;

    const DynamicArray<float>& samples = w.getSamples();
    for (int i = 0; i < samples.getSize(); ++i) {
        file << samples[i] << "\n";
    }

    file.close();
    return true;
}