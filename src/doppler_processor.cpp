#include "doppler_processor.h"
#include <cmath>

DopplerProcessor::DopplerProcessor(int np, double prf, double fc)
    : num_pulses_(np), prf_(prf), carrier_freq_(fc), wavelength_(3e8 / fc) {}

std::vector<Complex> DopplerProcessor::compute_doppler_fft(const std::vector<std::vector<Complex>>& pulse_data, int range_bin) {
    std::vector<Complex> slow_time(num_pulses_);
    for (int p = 0; p < num_pulses_ && p < (int)pulse_data.size(); p++)
        slow_time[p] = (range_bin < (int)pulse_data[p].size()) ? pulse_data[p][range_bin] : Complex(0,0);
    // Simple DFT
    int N = num_pulses_;
    std::vector<Complex> result(N);
    for (int k = 0; k < N; k++) {
        result[k] = Complex(0,0);
        for (int n = 0; n < N; n++)
            result[k] += slow_time[n] * std::exp(Complex(0, -2*M_PI*k*n/N));
    }
    return result;
}
double DopplerProcessor::velocity_from_bin(int bin) {
    double freq_res = prf_ / num_pulses_;
    double doppler_freq = (bin < num_pulses_/2) ? bin * freq_res : (bin - num_pulses_) * freq_res;
    return doppler_freq * wavelength_ / 2;
}
double DopplerProcessor::max_unambiguous_velocity() { return wavelength_ * prf_ / 4; }
