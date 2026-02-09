#include "range_doppler.h"
#include <cmath>

RangeDopplerMap::RangeDopplerMap(int nr, int nd) : num_range_(nr), num_doppler_(nd) {}

void RangeDopplerMap::compute(const std::vector<std::vector<Complex>>& pulse_matrix) {
    rd_map_.resize(num_range_, std::vector<double>(num_doppler_, 0));
    for (int r = 0; r < num_range_ && r < (int)pulse_matrix[0].size(); r++) {
        for (int d = 0; d < num_doppler_; d++) {
            Complex sum(0, 0);
            for (int p = 0; p < num_doppler_ && p < (int)pulse_matrix.size(); p++)
                sum += pulse_matrix[p][r] * std::exp(Complex(0, -2*M_PI*d*p/num_doppler_));
            rd_map_[r][d] = std::abs(sum);
        }
    }
}
std::vector<std::vector<double>> RangeDopplerMap::get_magnitude_db() {
    auto db = rd_map_;
    for (auto& row : db) for (auto& v : row) v = 20 * std::log10(v + 1e-10);
    return db;
}
