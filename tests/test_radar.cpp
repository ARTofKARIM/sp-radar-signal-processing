#include <iostream>
#include <cassert>
#include <cmath>
#include "signal_generator.h"
#include "pulse_compression.h"
#include "cfar_detector.h"

void test_chirp_generation() {
    RadarSignalGenerator gen(50e6, 10e-6, 100e6);
    auto chirp = gen.generate_chirp();
    assert(chirp.size() == 1000);
    assert(std::abs(chirp[0]) > 0.9);
    std::cout << "PASS: test_chirp_generation" << std::endl;
}
void test_range_resolution() {
    RadarSignalGenerator gen(50e6, 10e-6, 100e6);
    double res = gen.get_range_resolution();
    assert(std::abs(res - 3.0) < 0.1);
    std::cout << "PASS: test_range_resolution" << std::endl;
}
void test_cfar() {
    std::vector<double> signal(100, 1.0);
    signal[50] = 20.0;
    CFARDetector cfar(2, 8, 3.0);
    auto dets = cfar.detect(signal);
    assert(dets.size() >= 1);
    std::cout << "PASS: test_cfar" << std::endl;
}
int main() {
    test_chirp_generation();
    test_range_resolution();
    test_cfar();
    std::cout << "All radar tests passed!" << std::endl;
    return 0;
}
