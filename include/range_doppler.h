#pragma once
#include <vector>
#include <complex>
using Complex = std::complex<double>;

class RangeDopplerMap {
public:
    RangeDopplerMap(int num_range_bins, int num_doppler_bins);
    void compute(const std::vector<std::vector<Complex>>& pulse_matrix);
    std::vector<std::vector<double>> get_magnitude_db();
    int get_num_range_bins() const { return num_range_; }
    int get_num_doppler_bins() const { return num_doppler_; }
private:
    int num_range_, num_doppler_;
    std::vector<std::vector<double>> rd_map_;
};
