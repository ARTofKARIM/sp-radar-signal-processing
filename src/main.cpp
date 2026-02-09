#include <iostream>
#include "signal_generator.h"
#include "pulse_compression.h"
#include "cfar_detector.h"
#include "doppler_processor.h"

int main() {
    double bw = 50e6, pw = 10e-6, sr = 100e6, fc = 10e9;
    RadarSignalGenerator gen(bw, pw, sr);
    auto chirp = gen.generate_chirp();
    std::cout << "Chirp: " << chirp.size() << " samples" << std::endl;
    std::cout << "Range resolution: " << gen.get_range_resolution() << " m" << std::endl;
    auto rx = gen.generate_received(chirp, 5000, 100, fc);
    rx = gen.add_noise(rx, 15);
    PulseCompressor pc(2048);
    auto compressed = pc.matched_filter(rx, chirp);
    auto profile = pc.compute_range_profile(compressed, sr);
    CFARDetector cfar(4, 16, 5.0);
    auto dets = cfar.detect(profile);
    std::cout << "CFAR detections: " << dets.size() << std::endl;
    DopplerProcessor dp(64, 1000, fc);
    std::cout << "Max velocity: " << dp.max_unambiguous_velocity() << " m/s" << std::endl;
    return 0;
}
