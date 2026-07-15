# C++ Music Tune Visualizer

A C++ console application developed for CE 1337 Computer Science I. 
The program loads musical key information and tune files, processes note data, and generates a visual representation of a melody.

## Features

- Loads musical key data from external files
- Stores key information using structures
- Reads and processes tune files
- Searches for matching notes and frequencies
- Displays loaded keys and tune information
- Generates a console-based visualization of a tune

## Concepts Used

- C++ Structures (`struct`)
- Vectors
- File input/output (`fstream`)
- Dynamic memory allocation
- Functions
- Searching algorithms
- Data processing
- Console formatting

## Technologies

- C++
- Visual Studio
- Eclipse IDE

## How It Works

The program stores musical keys using a `Key` structure containing:
- Note letter
- Symbol
- Octave
- Frequency
- Wavelength

Tune notes are stored using a `Note` structure containing:
- Note letter
- Symbol
- Octave
- Duration

The program compares tune notes with available keys and draws the melody using different symbols based on note duration.

## Author

Danya Almintakh
