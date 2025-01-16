#include <time/delta_time.hpp>

#include <GLFW/glfw3.h>
#include <iostream>

Time::Time() {
    lastTime = 0.0f;
    frames_passed = 0;
    _time_passed_since_last_check = 0.0f;
}

void Time::Update() {
    // Get delta time
    time = glfwGetTime();
    delta = time - lastTime;
    lastTime = time;

    // Store the sum of the seconds since last check
    _time_passed_since_last_check += delta;

    frames_passed++;
}


double Time::GetDeltaTime() {
    return this->delta;
}

void Time::PrintDeltaTime(double update_frequency_seconds) {
    if (_time_passed_since_last_check > update_frequency_seconds) {
        std::cout << "Delta time: " << this->delta << "\n";
        _time_passed_since_last_check = 0.0f;
    }
}

uint32_t Time::GetFramesPassed() {
    return this->frames_passed;
}
