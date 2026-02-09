# Radar Signal Processing (C++)

High-performance radar signal processing library in C++17 with pulse compression, CFAR detection, Doppler processing, and range-Doppler map generation.

## Architecture
```
sp-radar-signal-processing/
├── include/ (signal_generator.h, pulse_compression.h, cfar_detector.h, doppler_processor.h, range_doppler.h)
├── src/ (matching .cpp files + main.cpp)
├── tests/test_radar.cpp
├── config/radar.yaml
└── CMakeLists.txt
```

## Build
```bash
mkdir build && cd build && cmake .. && make
./radar_processor
```

## Technologies
- C++17, CMake, STL









