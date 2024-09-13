#pragma once

#include <GLFW/glfw3.h>

#define bool char
#define true 1
#define false 0

enum RENDER_MODE {
    FILL = 0,
    LINES
};

// Process all keyboard events
void processInput(GLFWwindow *window, enum RENDER_MODE *render_mode, bool *is_key_pressed);
