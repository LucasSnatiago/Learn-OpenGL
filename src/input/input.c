#include <input/input.h>

void processInput(GLFWwindow *window, enum RENDER_MODE *render_mode, bool *is_key_pressed) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, 1);
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
        // Key just released
        *is_key_pressed = false;
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        // Looping through a pressed button
        if (*is_key_pressed)
            return;

        if (*render_mode == FILL) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            *render_mode = LINES;
        } else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            *render_mode = FILL;
        }

        // Key pressed
        *is_key_pressed = true;
    }
}
