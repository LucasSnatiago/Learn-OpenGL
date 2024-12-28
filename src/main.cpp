// OpenGL imports
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Standard Libraries Imports
#include <iostream>
#include <cmath>

// Local C++ libraries imports
#include <shaders/compiler.hpp>

// Local C Libraries imports
extern "C" {
    #include <window/resize.h>
    #include <input/input.h>
}


int main(int argc, char **argv, char **env) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwSetErrorCallback([](int error, const char* description) {
        std::cerr << "GLFW Error (" << error << "): " << description << std::endl;
    });

    GLFWwindow *window = glfwCreateWindow(800, 600, "Simple Window using OpenGL", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create a GLFW context!\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    // Called everytime the window is resized
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to load Glad context!\n";
        return -1;
    }

    // Creating shaders
    Shader ourShader("../src/shaders/shader.vert", "../src/shaders/shader.frag");

    // Building the triangles
    // First 3 elements -> positions for the vertices
    // Last 3 elements  -> colors
    float vertices1[] = {
         // Position        // Colors
         0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // top right RED
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right GREEN
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f  // bottom left BLUE
    };

    // Generating an array information needed for opengl
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Setup for the first triangle
    // Bind Vertex Array Object
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

    // Interpreting my triangle position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Interpreting my triangle color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    enum RENDER_MODE render = FILL;
    char isKeyPressed = 0;
    // Program main loop
    while (!glfwWindowShouldClose(window)) {
        // Process input events
        processInput(window, &render, &isKeyPressed);

        // Clear Background
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ourShader.use();

        // Render triangle
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Freeing all resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}
