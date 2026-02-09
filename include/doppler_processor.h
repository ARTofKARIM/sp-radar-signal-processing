#pragma once
#include <vector>
#include <complex>
using Complex = std::complex<double>;

class DopplerProcessor {
public:
    DopplerProcessor(int num_pulses, double prf, double carrier_freq);
    std::vector<Complex> compute_doppler_fft(const std::vector<std::vector<Complex>>& pulse_data, int range_bin);
    double velocity_from_bin(int doppler_bin);
    double max_unambiguous_velocity();
private:
    int num_pulses_;
    double prf_, carrier_freq_, wavelength_;
};
