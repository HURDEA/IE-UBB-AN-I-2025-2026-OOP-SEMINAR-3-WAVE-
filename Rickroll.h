/**
 * @file Rickroll.h
 * @brief Declaration of the algorithmic melody sequence generator.
 * * This header exposes the interface for generating the custom synthesizer track,
 * abstracting the sequence data away from the main application logic.
 */

#pragma once

 /**
  * @brief Generates a specific melodic sequence ("Rickroll") and saves it to disk.
  * * Utilizes the SynthesizerTrack class to sequence a series of square wave notes
  * based on predetermined frequencies and a specified BPM tempo. The final output
  * is serialized to 'rickroll.csv'.
  */
void generateRickrollSequence();