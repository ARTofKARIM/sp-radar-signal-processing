#pragma once
#include <vector>
#include <complex>
using Complex = std::complex<double>;

class RadarSignalGenerator {
public:
    RadarSignalGenerator(double bandwidth, double pulse_width, double sample_rate);
    std::vector<Complex> generate_chirp();
    std::vector<Complex> generate_received(const std::vector<Complex>& tx, double range_m, double velocity_mps,
                                            double carrier_freq, double rcs = 1.0);
    std::vector<Complex> add_noise(const std::vector<Complex>& signal, double snr_db);
    double get_range_resolution() const;
private:
    double bandwidth_, pulse_width_, sample_rate_;
    int num_samples_;
};
