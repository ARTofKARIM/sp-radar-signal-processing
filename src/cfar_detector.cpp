#include "cfar_detector.h"
#include <algorithm>
#include <numeric>

CFARDetector::CFARDetector(int guard, int training, double factor)
    : guard_cells_(guard), training_cells_(training), threshold_factor_(factor) {}

std::vector<double> CFARDetector::compute_threshold(const std::vector<double>& signal) {
    int n = signal.size(), half_win = guard_cells_ + training_cells_;
    std::vector<double> thresh(n, 0);
    for (int i = half_win; i < n - half_win; i++) {
        double sum = 0; int count = 0;
        for (int j = i - half_win; j < i - guard_cells_; j++) { sum += signal[j]; count++; }
        for (int j = i + guard_cells_ + 1; j <= i + half_win; j++) { sum += signal[j]; count++; }
        thresh[i] = threshold_factor_ * sum / (count > 0 ? count : 1);
    }
    return thresh;
}
std::vector<Detection> CFARDetector::detect(const std::vector<double>& signal) {
    auto thresh = compute_threshold(signal);
    std::vector<Detection> dets;
    for (size_t i = 0; i < signal.size(); i++)
        if (signal[i] > thresh[i]) dets.push_back({(int)i, signal[i], thresh[i]});
    return dets;
}
