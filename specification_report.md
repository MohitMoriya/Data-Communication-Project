# Project Specification Report: Digital Signal Encoder and Decoder
**Course:** ITT 036 (Programming Assignment 1)  
**Deliverable Date:** 21 October 2026  
**Language & Platform:** C++17 on Windows / MinGW-w64 (GCC 16.2), CMake 4.4, Ninja

---

### 1. Overview & Architecture
This project implements a complete digital signal encoder and decoder system in C++ with graphical visualization and pixel-based decoding for extra credit.

The design strictly follows modern Object-Oriented software engineering principles:
- **Strategy & Factory Registry Pattern:** To avoid massive `switch` or `if/else` ladders (fulfilling the competitive coding requirement), all line coding schemes inherit from an `Encoder` interface and are registered into a factory table mapping `Scheme` enums to lambda instantiation constructors.
- **Competitive Coding Optimization (Palindrome):** Implemented **Manacher's Algorithm** to compute the longest palindromic bit subsequence in **$O(N)$** linear time and space, inserting delimiter tokens to handle both even- and odd-length palindromes uniformly.
- **Scrambling Zero-Run Detection:** Implemented in $O(N)$ linear scans with violation-tracking state machines for both B8ZS (`000VB0VB`) and HDB3 (`000V`/`B00V`).

---

### 2. Line Coding & Modulation Implementations
1. **NRZ-L:** High level (+V) represents bit 1; Low level (-V) represents bit 0.
2. **NRZ-I:** Inversion on bit 1; level remains constant on bit 0 (initial reference: -V).
3. **Manchester (IEEE 802.3):** Low-to-high mid-bit transition represents 1; high-to-low represents 0.
4. **Differential Manchester:** Mid-bit transition always occurs. Bit 0 exhibits a transition at bit interval start; Bit 1 exhibits no start transition.
5. **Bipolar AMI:** Bit 0 is 0V; Bit 1 alternates between +V and -V.
6. **B8ZS Scrambling:** Substitutes 8 consecutive zeros with `000VB0VB`, maintaining DC balance and synchronization.
7. **HDB3 Scrambling:** Substitutes 4 consecutive zeros with either `000V` or `B00V` depending on the parity of pulses since the last substitution.
8. **Pulse Code Modulation (PCM):** Synthesizes continuous-time analog input, samples at sampling frequency $f_s \ge 2 f_{max}$, uniformly quantizes across $2^n$ levels, and serializes into $n$-bit binary codewords.
9. **Delta Modulation (DM):** Reconstructs an approximation staircase using a 1-bit comparator ($\Delta$ step up when signal exceeds estimate, $\Delta$ step down otherwise).

---

### 3. Graphical Interface & Visualization (SFML 3)
A custom hardware-accelerated GUI renderer was developed using **SFML 3 (Simple and Fast Multimedia Library)**:
- **Top Panel (Analog Mode):** Renders the smooth analog waveform, PAM sample points (circles), and reconstructed staircase approximations (PCM/DM).
- **Bottom Panel:** Renders the line-coded waveform with a custom digital grid, voltage indicators (+V, 0, -V), per-bit numeric labels, and a highlighted region marking the longest palindrome.
- **Headless & GUI Modes:** Supports both interactive window display and automatic PNG export (`signal.png`).

---

### 4. Extra Credit: Parameter & Image-Based Line Decoder
Unlike traditional decoders that read memory variables or binary arrays, the extra credit decoder parses the rendered **`signal.png` image directly from disk**:
1. It calculates the exact bounding box and coordinate transformation matrix of the line coding panel.
2. It samples pixel columns at $t = i + 0.25$ and $t = i + 0.75$ into each bit interval.
3. It detects the green trace pixels (`sf::Color(80, 230, 150)`) by color thresholding and computes distance to the $+V$, $0$, and $-V$ horizontal rails.
4. It performs rule-based demodulation (level inspection for NRZ-L, boundary transition detection for NRZ-I/Diff Manchester, mid-bit direction for Manchester, and pulse/scramble descrambling for AMI/B8ZS/HDB3).
5. **Result:** Achieves 100% verification accuracy when checked against the original transmitted bits.

---

### 5. Assumptions Considered
- Initial line voltage reference before bit 0 is assumed to be $-V$ for differential schemes (NRZ-I and Differential Manchester).
- First non-zero pulse in AMI is positive ($+V$).
- Sampling frequency $f_s$ must satisfy the Nyquist-Shannon criterion ($f_s \ge 2 f$).

---

### 6. References
1. Stallings, W. *Data and Computer Communications*, 10th Ed., Pearson (Line Coding & Scrambling).
2. Forouzan, B. A. *Data Communications and Networking*, 5th Ed., McGraw-Hill.
3. Manacher, G. (1975). *A New Linear-Time "On-Line" Algorithm for Finding the Smallest Initial Palindrome of a String*. Journal of the ACM.
4. SFML 3.0 Documentation: [https://www.sfml-dev.org/documentation/3.0.0/](https://www.sfml-dev.org/documentation/3.0.0/)
