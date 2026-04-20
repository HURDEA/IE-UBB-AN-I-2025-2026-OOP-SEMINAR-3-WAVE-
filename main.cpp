/**
 * @file Seminar 3.cpp
 * @brief Primary application entry point.
 * * Integrates the standard acoustic wave experiments and the custom synthesizer
 * sequence generator into a single executable pipeline.
 */

#include <iostream>
#include "Wave.h"
#include "Rickroll.h"

 /**
  * @brief Executes standard laboratory experiments related to acoustic waves.
  * * Generates standard waveform experiments, Tremolo, and Robot audio effects,
  * serializing the sample arrays to localized CSV files.
  */
void runStandardExperiments() {
    std::cout << "Generating standard acoustic experiments...\n";

    float duration = 2.0f;
    float sr = 44100.0f;

    // Tremolo Effect
    SineWave carrier_tremolo(440.0f, 0.8f, sr);
    carrier_tremolo.computeSamples(duration);
    SineWave modulator_tremolo(5.0f, 1.0f, sr);
    modulator_tremolo.computeSamples(duration);

    AcousticWave tremolo = carrier_tremolo * modulator_tremolo;
    WaveOutput::saveSamples("tremolo.csv", tremolo);

    // Robot Effect
    SineWave carrier_robot(440.0f, 0.8f, sr);
    carrier_robot.computeSamples(duration);
    SquareWave gate_robot(8.0f, 1.0f, sr);
    gate_robot.computeSamples(duration);

    AcousticWave robot = carrier_robot * gate_robot;
    WaveOutput::saveSamples("robot.csv", robot);
}

/**
 * @brief Main execution routine.
 * @return Execution status code.
 */
int main() {
    std::cout << "Starting audio generation protocol...\n";

    runStandardExperiments();
    generateRickrollSequence();

    std::cout << "All processes completed successfully. Execute Python conversion script to finalize WAV generation.\n";
    return 0;
}