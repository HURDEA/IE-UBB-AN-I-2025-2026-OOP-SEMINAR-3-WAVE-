#include "MorseEncoder.h"
#include "Silence.h"
#include <fstream>
#include <iostream>

std::map<char, std::string> MorseEncoder::alphabet;

void MorseEncoder::loadAlphabet(const std::string& filename) {
    std::ifstream file(filename);
    char character;
    std::string morse;
    if (file.is_open()) {
        while (file >> character >> morse) {
            alphabet[toupper(character)] = morse;
        }
        file.close();
    }
    else {
        std::cerr << "Error loading " << filename << "\n";
    }
}

AcousticWave MorseEncoder::encode(const std::string& s) {
    const float frequency = 700.0f;
    const float amplitude = 0.8f;
    const float sr = 44100.0f;
    const float timeUnit = 0.1f;

    // Create the base components
    SineWave ditBase(frequency, amplitude, sr);
    SineWave dahBase(frequency, amplitude, sr);
    Silence gapBase(sr);

    // Pre-compute components
    SineWave dit = ditBase; dit.computeSamples(timeUnit * 1);
    SineWave dah = dahBase; dah.computeSamples(timeUnit * 3);
    Silence interElementGap = gapBase; interElementGap.computeSamples(timeUnit * 1);
    Silence shortGap = gapBase; shortGap.computeSamples(timeUnit * 3);
    Silence mediumGap = gapBase; mediumGap.computeSamples(timeUnit * 7);

    AcousticWave transmission(frequency, amplitude, sr, "Morse Transmission");
    bool firstChar = true;

    for (char c : s) {
        if (c == ' ') {
            transmission = transmission + mediumGap;
            firstChar = true;
            continue;
        }

        c = toupper(c);
        if (alphabet.find(c) != alphabet.end()) {
            if (!firstChar) {
                transmission = transmission + shortGap;
            }

            std::string sequence = alphabet[c];
            for (size_t i = 0; i < sequence.length(); ++i) {
                if (sequence[i] == '.') {
                    transmission = transmission + dit;
                }
                else if (sequence[i] == '-') {
                    transmission = transmission + dah;
                }

                if (i < sequence.length() - 1) {
                    transmission = transmission + interElementGap;
                }
            }
            firstChar = false;
        }
    }
    return transmission;
}