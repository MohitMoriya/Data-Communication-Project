# Digital Signal Encoder and Decoder - Project Plan

This document outlines a structured, step-by-step plan for implementing the Digital Signal Encoder and Decoder project in C++. 

## 1. Architecture & Tech Stack
*   **Language:** C++ (Qualifies for extra credit per the assignment guidelines).
*   **Build System:** CMake (Recommended for managing dependencies and compiling).
*   **Graphics Library:** SFML (Simple and Fast Multimedia Library) combined with ImGui/ImPlot, OR Matplotlib-cpp (a C++ wrapper for Python's matplotlib) for simpler plotting if raw OpenGL is too complex. Raw OpenGL is also an option but requires more boilerplate.
*   **Design Pattern:** Strategy Pattern (To avoid massive if/else or switch statements for the different encoding schemes, fulfilling the competitive coding requirement).

## 2. Implementation Phases

### Phase 1: Core CLI & Input Handling
*   **Objective:** Create the user interface for inputting data and selecting modes.
*   **Tasks:**
    *   Create a CLI menu asking if the input is Analog or Digital.
    *   If Digital: Ask for scheme (NRZ-L, NRZ-I, Manchester, Differential Manchester, AMI).
    *   If AMI: Ask if scrambling is needed (B8ZS, HDB3).
    *   If Analog: Ask for PCM or DM.

### Phase 2: Digital Data Generation & Optimization
*   **Objective:** Generate random binary data and implement the optimized palindrome algorithm.
*   **Tasks:**
    *   Implement a `DataGenerator` class.
    *   Generate a purely random bit sequence.
    *   Generate a random bit sequence with guaranteed runs of 4 or 8 consecutive zeros (for scrambling testing).
    *   **Competitive Coding (Longest Palindrome):** Implement **Manacher's Algorithm** to find the longest palindromic sequence in $O(N)$ time complexity. This will secure maximum marks for the optimization requirement.

### Phase 3: Line Coding & Scrambling (Polymorphic Design)
*   **Objective:** Implement the digital-to-digital encoding schemes without massive if/else chains.
*   **Tasks:**
    *   Define an `Encoder` interface with an `encode(const std::vector<int>& data)` method.
    *   Implement derived classes: `NRZL`, `NRZI`, `Manchester`, `DiffManchester`, `AMI`.
    *   Implement Scrambling decorators or specific classes for `B8ZS` and `HDB3`.
    *   **Optimization:** Use a map of enums to factory functions (or objects) to select the encoder dynamically at runtime rather than using a giant switch statement.

### Phase 4: Analog to Digital Conversion
*   **Objective:** Implement PCM and DM.
*   **Tasks:**
    *   **PCM (Pulse Code Modulation):** Implement sampling, quantization, and encoding steps to convert an analog wave (e.g., sine wave) into a digital bitstream.
    *   **DM (Delta Modulation):** Implement 1-bit quantization based on the difference between the current sample and the previous approximated signal.
    *   Feed the resulting bitstream back into the line coders from Phase 3.

### Phase 5: Graphical Output (Plotting)
*   **Objective:** Visualize the digital bitstream, encoded signals, and stair-case signals.
*   **Tasks:**
    *   Set up the chosen C++ graphics library (e.g., SFML/ImPlot).
    *   Map the encoded voltage levels (e.g., +V, 0, -V) to Y-coordinates.
    *   Draw the square waves and staircase signals based on the data points.
    *   Ensure the plot axes are labeled and the longest palindrome is highlighted or printed.

### Phase 6: Extra Credit (Image/Parameter-based Decoding)
*   **Objective:** Decode the signal back to digital data by analyzing the graphical signal parameters.
*   **Tasks:**
    *   Instead of simply reversing the array logic, read the plotted line segments (voltage levels and transitions).
    *   Determine bit values based on whether the signal stays high, low, or transitions in the middle of the clock cycle.
    *   Output the decoded digital stream and compare it with the original to verify accuracy.

## 3. Recommended Directory Structure
```text
project/
├── CMakeLists.txt
├── src/
│   ├── main.cpp
│   ├── cli.cpp
│   ├── DataGenerator.cpp
│   ├── encoders/
│   │   ├── Encoder.h
│   │   ├── NRZ.cpp
│   │   ├── Manchester.cpp
│   │   └── AMI.cpp
│   ├── modulation/
│   │   ├── PCM.cpp
│   │   └── DM.cpp
│   └── graphics/
│       └── Plotter.cpp
└── include/
    └── (header files)
```

## 4. Next Steps to Begin
1.  Confirm the graphics library you want to use (SFML vs OpenGL vs Matplotlib-cpp).
2.  Set up the C++ project environment and `CMakeLists.txt`.
3.  Start with Phase 1 (CLI) and Phase 2 (Data Generation / Manacher's Algorithm).
