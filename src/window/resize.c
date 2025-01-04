#include <window/resize.h>

void framebuffer_size_callback(GLFWwindow *screen, GLsizei width, GLsizei heigth) {
    glViewport(0, 0, width, heigth);
}
