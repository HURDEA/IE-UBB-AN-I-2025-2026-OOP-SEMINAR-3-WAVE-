# Acoustic Wave Generator & Synthesizer

## Overview
This project is an object-oriented C++ application designed to generate, modulate, and sequence fundamental acoustic waveforms. It serves as an exploration of digital signal processing fundamentals, class hierarchies, and memory management in C++.

The application serializes generated audio data into `.csv` files, which are subsequently converted into playable standard `.wav` audio files via an included Python conversion script.

## Features
* **Custom Memory Management:** Implements a generic, templated `DynamicArray<T>` class enforcing the Rule of Three for safe, contiguous memory allocation of floating-point audio samples.
* **Waveform Generation:** Computes mathematical models for primary acoustic waveforms:
  * Sine Wave
  * Square Wave
  * Triangle Wave
  * Sawtooth Wave
* **Amplitude Modulation (AM):** Utilizes standard operator overloading to modulate carrier wave amplitudes, producing distinct audio effects:
  * **Tremolo Effect:** Low-frequency sine wave modulation.
  * **Robot/Gated Effect:** Low-frequency square wave modulation.
* **Algorithmic Sequencer:** Features a `SynthesizerTrack` class capable of sequencing distinct musical notes based on specified frequencies, durations, and a defined Beats Per Minute (BPM) tempo.

## Project Structure
* `DynamicArray.h` / `.tpp` - Templated dynamic array container for sample management.
* `Wave.h` / `.cpp` - Core acoustic wave base class and specific waveform derivations.
* `Rickroll.h` / `.cpp` - Custom algorithmic melody sequencer module.
* `Seminar 3.cpp` - Main execution pipeline.
* `to_wav.py` - Python utility script for converting raw CSV samples to formatted WAV audio.

## Prerequisites
* **C++ Compiler:** Compatible with C++11 or higher (Visual Studio / MSVC recommended).
* **Python 3.x:** Required to execute the `to_wav.py` conversion script.
* **Doxygen (Optional):** Required to regenerate the HTML/LaTeX documentation.

## Compilation and Execution

### 1. Build the C++ Application
Open the project in Visual Studio and compile the solution (`Ctrl + Shift + B`). Run the generated executable. The program will silently compute the sample arrays and output the following files to the working directory:
* `tremolo.csv`
* `robot.csv`
* `rickroll.csv`

### 2. Convert Data to Audio
Open a command-line interface in the directory containing the generated `.csv` files and the Python script. Execute the following command to process all files in the current directory:

```bash
python to_wav.py --input .