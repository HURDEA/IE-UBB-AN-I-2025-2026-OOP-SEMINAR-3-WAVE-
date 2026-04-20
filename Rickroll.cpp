/**
 * @file Rickroll.cpp
 * @brief Implementation of the algorithmic melody sequence generator.
 * * Contains the specific frequency constants and timing logic required to generate
 * the custom synthesizer track.
 */

#include "Rickroll.h"
#include "Wave.h"
#include <iostream>

namespace {
    /** @brief Frequency for note F4 in Hertz. */
    const float F4 = 349.23f;
    /** @brief Frequency for note G4 in Hertz. */
    const float G4 = 392.00f;
    /** @brief Frequency for note A4 in Hertz. */
    const float A4 = 440.00f;
    /** @brief Frequency for note Bb4 in Hertz. */
    const float Bb4 = 466.16f;
    /** @brief Frequency for note C5 in Hertz. */
    const float C5 = 523.25f;
    /** @brief Frequency for note D5 in Hertz. */
    const float D5 = 587.33f;
}

void generateRickrollSequence() {
    std::cout << "Sequencing synthesizer track (Rickroll)...\n";

    SynthesizerTrack track(44100.0f);

    float bpm = 114.0f;
    float q = 60.0f / bpm;
    float e = q / 2.0f;
    float h = q * 2.0f;

    // Sequence Block 1
    track.addNote(F4, e);
    track.addNote(G4, e);
    track.addNote(Bb4, e);
    track.addNote(F4, e);
    track.addNote(D5, q);
    track.addNote(D5, q);
    track.addNote(C5, h);

    // Sequence Block 2
    track.addNote(F4, e);
    track.addNote(G4, e);
    track.addNote(Bb4, e);
    track.addNote(F4, e);
    track.addNote(C5, q);
    track.addNote(C5, q);
    track.addNote(Bb4, q);
    track.addNote(A4, e);
    track.addNote(G4, e);

    // Sequence Block 3
    track.addNote(F4, e);
    track.addNote(G4, e);
    track.addNote(Bb4, e);
    track.addNote(F4, e);
    track.addNote(Bb4, q);
    track.addNote(C5, q);
    track.addNote(A4, q);
    track.addNote(F4, e);
    track.addNote(F4, e);
    track.addNote(C5, q);
    track.addNote(Bb4, h);

    std::cout << "Saving sequence to rickroll.csv...\n";
    WaveOutput::saveSamples("rickroll.csv", track);
}