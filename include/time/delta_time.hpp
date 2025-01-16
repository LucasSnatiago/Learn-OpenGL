#pragma once

#include <cstdint>

class Time {
    double time; // Time passed since app started
    double lastTime; // Time passed since app started (one frame ago)
    double delta; // Difference in seconds between the last two frames
    uint32_t frames_passed; // Frames passed since app started screen

    double _time_passed_since_last_check;
public:
    // Starting values
    Time();

    // Update time every frame
    void Update();

    double GetDeltaTime();
    void PrintDeltaTime(double update_frequency_seconds);
    uint32_t GetFramesPassed();
};
