#include <window/resize.h>

void framebuffer_size_callback(GLFWwindow *screen, int width, int heigth) {
    glViewport(0, 0, width, heigth);
}
