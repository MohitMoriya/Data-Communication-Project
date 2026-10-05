#pragma once
#include <string>
#include <vector>

namespace codec {

using Bits = std::vector<int>;

class DataGenerator {
public:
    // Purely random bit sequence of given length.
    static Bits random(size_t length);

    // Random sequence guaranteed to contain a run of `zeroRun` (4 or 8) zeros,
    // for testing HDB3 / B8ZS scrambling.
    static Bits randomWithZeroRun(size_t length, size_t zeroRun);

    static Bits fromString(const std::string& s);   // "10110" -> {1,0,1,1,0}
    static std::string toString(const Bits& bits);
};

// Longest palindromic substring of a bit sequence using Manacher's algorithm, O(N).
struct PalindromeResult {
    size_t start = 0;
    size_t length = 0;
};
PalindromeResult longestPalindrome(const Bits& bits);

} // namespace codec
