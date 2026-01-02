#include <input/mouse.h>

float yaw   = -90.0f;
float pitch =  0.0f;

float lastX = 400, lastY = 300;

// Firstmouse flag
char _firstMouse = 1;

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (_firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        _firstMouse = 0;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // Reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    const float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;
}
