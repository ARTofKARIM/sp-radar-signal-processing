#include "pulse_compression.h"
#include <cmath>
#include <algorithm>

PulseCompressor::PulseCompressor(int fft_size) : fft_size_(fft_size) {}

std::vector<Complex> PulseCompressor::fft(const std::vector<Complex>& x) {
    int N = x.size();
    if (N <= 1) return x;
    std::vector<Complex> even, odd;
    for (int i = 0; i < N; i++) { (i % 2 == 0 ? even : odd).push_back(x[i]); }
    auto Fe = fft(even), Fo = fft(odd);
    std::vector<Complex> result(N);
    for (int k = 0; k < N/2; k++) {
        Complex t = std::exp(Complex(0, -2*M_PI*k/N)) * Fo[k];
        result[k] = Fe[k] + t;
        result[k + N/2] = Fe[k] - t;
    }
    return result;
}
std::vector<Complex> PulseCompressor::ifft(const std::vector<Complex>& X) {
    auto conj_X = X;
    for (auto& x : conj_X) x = std::conj(x);
    auto result = fft(conj_X);
    for (auto& x : result) x = std::conj(x) / Complex(result.size(), 0);
    return result;
}
std::vector<Complex> PulseCompressor::matched_filter(const std::vector<Complex>& received, const std::vector<Complex>& reference) {
    int N = fft_size_;
    std::vector<Complex> rx_padded(N, Complex(0,0)), ref_padded(N, Complex(0,0));
    for (size_t i = 0; i < std::min(received.size(), (size_t)N); i++) rx_padded[i] = received[i];
    for (size_t i = 0; i < std::min(reference.size(), (size_t)N); i++) ref_padded[i] = reference[i];
    auto RX = fft(rx_padded), REF = fft(ref_padded);
    std::vector<Complex> product(N);
    for (int i = 0; i < N; i++) product[i] = RX[i] * std::conj(REF[i]);
    return ifft(product);
}
std::vector<double> PulseCompressor::compute_range_profile(const std::vector<Complex>& compressed, double sample_rate) {
    std::vector<double> profile(compressed.size());
    for (size_t i = 0; i < compressed.size(); i++) profile[i] = 20 * std::log10(std::abs(compressed[i]) + 1e-10);
    return profile;
}
