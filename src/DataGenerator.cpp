#include "DataGenerator.h"

#include <algorithm>
#include <random>

namespace codec {

static std::mt19937& rng() {
    static std::mt19937 gen{std::random_device{}()};
    return gen;
}

Bits DataGenerator::random(size_t length) {
    std::uniform_int_distribution<int> d(0, 1);
    Bits b(length);
    for (auto& x : b) x = d(rng());
    return b;
}

Bits DataGenerator::randomWithZeroRun(size_t length, size_t zeroRun) {
    if (length < zeroRun) length = zeroRun;
    Bits b = random(length);
    std::uniform_int_distribution<size_t> pos(0, length - zeroRun);
    size_t p = pos(rng());
    std::fill(b.begin() + p, b.begin() + p + zeroRun, 0);
    return b;
}

Bits DataGenerator::fromString(const std::string& s) {
    Bits b;
    for (char c : s)
        if (c == '0' || c == '1') b.push_back(c - '0');
    return b;
}

std::string DataGenerator::toString(const Bits& bits) {
    std::string s;
    for (int x : bits) s += char('0' + x);
    return s;
}

PalindromeResult longestPalindrome(const Bits& bits) {
    if (bits.empty()) return {};
    // Transform: insert separators (-1) so odd/even palindromes are handled uniformly.
    std::vector<int> t;
    t.reserve(bits.size() * 2 + 1);
    t.push_back(-1);
    for (int x : bits) { t.push_back(x); t.push_back(-1); }

    const int n = static_cast<int>(t.size());
    std::vector<int> p(n, 0);
    int center = 0, right = 0;
    for (int i = 0; i < n; ++i) {
        if (i < right) p[i] = std::min(right - i, p[2 * center - i]);
        while (i - p[i] - 1 >= 0 && i + p[i] + 1 < n &&
               t[i - p[i] - 1] == t[i + p[i] + 1])
            ++p[i];
        if (i + p[i] > right) { center = i; right = i + p[i]; }
    }

    int best = 0, bestCenter = 0;
    for (int i = 0; i < n; ++i)
        if (p[i] > best) { best = p[i]; bestCenter = i; }

    return { static_cast<size_t>((bestCenter - best) / 2), static_cast<size_t>(best) };
}

} // namespace codec
