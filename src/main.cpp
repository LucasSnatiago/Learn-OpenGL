#define GLFW_INCLUDE_NONE
#define STB_IMAGE_IMPLEMENTATION

// OpenGL imports
#include <glad/gl.h>
#include <GLFW/glfw3.h>

// Standard Libraries Imports
#include <iostream>
#include <cmath>

// System imports for standarlization of code types
#include <stddef.h>

// Local C++ libraries imports
#include <shaders/compiler.hpp>

// Local C Libraries imports
extern "C" {
    #include <stb_image.h>
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

    if (!gladLoadGL(glfwGetProcAddress)) {
        std::cerr << "Failed to load Glad context!\n";
        return -1;
    }

    // Creating shaders
    Shader ourShader("./src/shaders/shader.vert", "./src/shaders/shader.frag");

    // Setting all 2D texture settings
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Texture will be mirrored on the edges of the screen
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_MIRRORED_REPEAT);

    // Texture filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Loading textures
    int32_t width, height, nrChannels;
    unsigned char *data = stbi_load("textures/container.jpg", &width, &height, &nrChannels, 0);

    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

    } else {
        std::cerr << "Failed to load texture from disk\n";
        std::exit(EXIT_FAILURE);

    }

    // Freeing image from RAM, keeping it in OpenGL driver only
    stbi_image_free(data);

    // Building the triangles
    // First 3 elements  -> positions for the vertices
    // Second 3 elements -> colors
    // Third 2 elements  -> texture coordenates
    GLfloat vertices[] = {
         // Position          // Colors           // Texture position
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top right
    };

    // Triangle positions
    GLint indices[] {
        0, 1, 3, // First triangle
        1, 2, 3  // Second triangle
    };

    // Generating an array information needed for opengl
    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Setup for the first triangle
    // Bind Vertex Array Object
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(0*sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
    // Color attibute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    // Texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6*sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

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

        // Bind texture
        glBindTexture(GL_TEXTURE_2D, texture);

        // Render container
        ourShader.use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Freeing all resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}
