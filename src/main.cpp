// OpenGL imports
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Standard Libraries Imports
#include <iostream>

// Local Libaries import
#include <window/resize.h>
#include <input/input.h>

int main(int argc, char **argv) {
    glfwInit();

    glfwSetErrorCallback([](int error, const char* description) {
        std::cerr << "GLFW Error (" << error << "): " << description << std::endl;
    });

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "Simple Window using OpenGL", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create a GLFW context!\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to load Glad context!\n";
        return -1;
    }

    // Initial window size
    glViewport(0, 0, 800, 600);
    // Called everytime the window is resized
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    while (!glfwWindowShouldClose(window)) {
        // Process input events
        processInput(window);

        // Render image

        // Check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glfwTerminate();

    return 0;
}
