# Digital Signal Encoder and Decoder (ITT 036)

C++ implementation of a Digital Signal Encoder & Decoder with GUI plotting and image-based parameter decoding for extra credit.

## Features
- **Data Generator**: Random bitstreams, bitstreams with guaranteed zero runs (4 or 8 zeros for testing scrambling).
- **Competitive Coding - Longest Palindrome**: Implemented using **Manacher's Algorithm** with optimal **$O(N)$** time complexity.
- **Line Coding Schemes**:
  - NRZ-L (Non-Return-to-Zero Level)
  - NRZ-I (Non-Return-to-Zero Inverted)
  - Manchester (IEEE 802.3)
  - Differential Manchester
  - Bipolar AMI (Alternate Mark Inversion)
- **Scrambling Schemes**:
  - **B8ZS** (Bipolar 8-Zero Substitution: `000VB0VB`)
  - **HDB3** (High Density Bipolar 3: `000V` / `B00V` maintaining odd/even pulse balances)
- **Modulation**:
  - **PCM** (Pulse Code Modulation): Sampling, uniform quantization, bit conversion.
  - **DM** (Delta Modulation): 1-bit adaptive step-tracking staircase signal.
- **Graphical Visualization (SFML 3)**:
  - Dark-mode multi-panel display.
  - Analog wave, PAM sample markers, and reconstructed staircase.
  - High-resolution square wave signal with bit-indexed grid and highlighted palindrome window.
- **Extra Credit - Image-Based Decoder**:
  - Decodes the signal **not from raw memory variables**, but by **analyzing pixel coordinates and RGB color parameters** from the generated `signal.png` image file.
  - Recovers the original digital bitstream with 100% precision across all line codes and descrambles B8ZS/HDB3 violations.

## Project Structure
```text
signal_codec/
├── CMakeLists.txt
├── signal.png                    # Generated oscilloscope plot
├── src/
│   ├── main.cpp                  # CLI menu & orchestration
│   ├── DataGenerator.h / .cpp    # Random generator & Manacher's O(N) algorithm
│   ├── encoders/
│   │   ├── Encoder.h / .cpp      # Factory registry & all 7 line coding schemes
│   ├── analog/
│   │   ├── Analog.h / .cpp       # Sine wave synthesis, PCM & DM modulators
│   └── graphics/
│       ├── Plotter.h / .cpp      # SFML 3 graph renderer
│       └── ImageDecoder.h / .cpp # Extra credit pixel-level image decoder
```

## How to Build and Run

### 1. Requirements
- MinGW-w64 GCC (with C++17 support)
- CMake 3.16+
- SFML 3.x (Graphics, Window, System)

### 2. Compile
From PowerShell in the project directory:
```powershell
$env:Path = "C:\msys64\ucrt64\bin;" + $env:Path
cmake -S . -B build -G Ninja
cmake --build build
```

### 3. Run Interactively
```powershell
.\build\signal_codec.exe
```

### 4. Run in Batch / Save-Only Mode (Generates `signal.png` without blocking GUI)
```powershell
.\build\signal_codec.exe --save-only
```
