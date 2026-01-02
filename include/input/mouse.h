#ifndef INPUT_MOUSE_H
#define INPUT_MOUSE_H

#include <GLFW/glfw3.h>

extern float yaw;
extern float pitch;
extern float lastX;
extern float lastY;
extern char _firstMouse;

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

#endif // INPUT_MOUSE_H
