#pragma once
#include <vector>
#include <complex>
using Complex = std::complex<double>;

class PulseCompressor {
public:
    PulseCompressor(int fft_size);
    std::vector<Complex> matched_filter(const std::vector<Complex>& received, const std::vector<Complex>& reference);
    std::vector<double> compute_range_profile(const std::vector<Complex>& compressed, double sample_rate);
private:
    int fft_size_;
    std::vector<Complex> fft(const std::vector<Complex>& x);
    std::vector<Complex> ifft(const std::vector<Complex>& X);
};
