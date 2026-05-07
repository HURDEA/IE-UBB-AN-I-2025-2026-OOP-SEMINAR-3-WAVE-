/**
 * @file main.cpp
 * @brief Primary application entry point.
 * * Integrates the standard acoustic wave experiments, custom synthesizer
 * sequence generator, and the new Morse code transmitter into a single pipeline.
 */

#include <iostream>
#include <string>
#include "Wave.h"
#include "Rickroll.h"
#include "MorseEncoder.h"
#include "SignalProcessor.h"

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
    std::cout << "Starting audio generation protocol...\n\n";

    // 1. Existing Seminar 3 functionality
    runStandardExperiments();
    std::cout << "\n";
    generateRickrollSequence();
    std::cout << "\n";

    // 2. Seminar 4: Morse Code Transmitter CLI
    // Ensure "morse.txt" is in the same directory as your executable
    MorseEncoder::loadAlphabet("morse.txt");

    std::cout << "--- Morse Code Transmitter ---\n";

    char choice;
    do {
        std::string message;
        std::string filename;

        std::cout << "Enter message: ";
        // std::ws safely extracts any leading whitespace or leftover newlines in the buffer
        std::getline(std::cin >> std::ws, message);

        std::cout << "Enter filename: ";
        std::getline(std::cin, filename);

        // Encode the string to Morse audio
        AcousticWave finalWave = MorseEncoder::encode(message);

        // Apply echo effect (e.g., 0.4s delay, 50% attenuation)
        SignalProcessor::applyEcho(finalWave, 0.4f, 0.5f);

        // Calculate actual duration based on sample count
        float finalDuration = finalWave.getSampleCount() / 44100.0f;

        std::cout << "Encoded '" << message << "' (Length: " << finalDuration << " seconds).\n";

        // Save to file
        WaveOutput::saveSamples(filename, finalWave);
        std::cout << "File saved to " << filename << ".\n\n";

        std::cout << "Do you want to send another message? (y/n): ";
        std::cin >> choice;
        std::cout << "\n";

    } while (choice == 'y' || choice == 'Y');

    std::cout << "Exiting application.\n";
    std::cout << "All processes completed successfully. Execute Python conversion script to finalize WAV generation.\n";

    return 0;
}