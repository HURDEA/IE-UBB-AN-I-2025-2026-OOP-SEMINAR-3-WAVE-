#pragma once
#include <string>
#include <map>
#include "Wave.h"

/**
 * @brief Utility class to encode text into Morse Code audio waves.
 */
class MorseEncoder {
private:
    static std::map<char, std::string> alphabet;

public:
    /**
     * @brief Loads the Morse alphabet mappings from a file.
     * @param filename The path to the text file.
     */
    static void loadAlphabet(const std::string& filename);

    /**
     * @brief Encodes a given string into a concatenated AcousticWave.
     * @param s The input string to encode.
     * @return The AcousticWave representing the Morse code audio.
     */
    static AcousticWave encode(const std::string& s);
};