#pragma once
#include <vector>
struct Detection { int index; double power; double threshold; };

class CFARDetector {
public:
    CFARDetector(int guard_cells, int training_cells, double threshold_factor);
    std::vector<Detection> detect(const std::vector<double>& signal);
    std::vector<double> compute_threshold(const std::vector<double>& signal);
private:
    int guard_cells_, training_cells_;
    double threshold_factor_;
};
