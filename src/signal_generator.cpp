#include "signal_generator.h"
#include <cmath>
#include <random>

RadarSignalGenerator::RadarSignalGenerator(double bw, double pw, double sr)
    : bandwidth_(bw), pulse_width_(pw), sample_rate_(sr), num_samples_(int(pw * sr)) {}

std::vector<Complex> RadarSignalGenerator::generate_chirp() {
    std::vector<Complex> chirp(num_samples_);
    double k = bandwidth_ / pulse_width_;
    for (int i = 0; i < num_samples_; i++) {
        double t = i / sample_rate_;
        double phase = M_PI * k * t * t;
        chirp[i] = Complex(std::cos(phase), std::sin(phase));
    }
    return chirp;
}
std::vector<Complex> RadarSignalGenerator::generate_received(const std::vector<Complex>& tx, double range_m,
    double velocity, double carrier_freq, double rcs) {
    double c = 3e8;
    int delay_samples = int(2 * range_m / c * sample_rate_);
    double doppler_shift = 2 * velocity * carrier_freq / c;
    double attenuation = rcs / (range_m * range_m + 1);
    std::vector<Complex> rx(tx.size() + delay_samples, Complex(0, 0));
    for (size_t i = 0; i < tx.size(); i++) {
        double t = i / sample_rate_;
        Complex doppler(std::cos(2*M_PI*doppler_shift*t), std::sin(2*M_PI*doppler_shift*t));
        rx[i + delay_samples] = attenuation * tx[i] * doppler;
    }
    return rx;
}
std::vector<Complex> RadarSignalGenerator::add_noise(const std::vector<Complex>& signal, double snr_db) {
    std::mt19937 rng(42);
    std::normal_distribution<> dist(0, 1);
    double sig_power = 0;
    for (auto& s : signal) sig_power += std::norm(s);
    sig_power /= signal.size();
    double noise_power = sig_power * std::pow(10, -snr_db / 10);
    std::vector<Complex> noisy = signal;
    for (auto& s : noisy) s += std::sqrt(noise_power/2) * Complex(dist(rng), dist(rng));
    return noisy;
}
double RadarSignalGenerator::get_range_resolution() const { return 3e8 / (2 * bandwidth_); }
