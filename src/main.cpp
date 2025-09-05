#define GLFW_INClUDE_NONE
#define STB_IMAGE_IMPLEMENTATION

// OpenGL imports
// #include <vulkan/vulkan.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

// OpenGL Math import
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Standard Libraries Imports
#include <iostream>
#include <cmath>

// System imports for standarlization of code types
#include <stddef.h>

// Local C++ libraries imports
#include <shaders/compiler.hpp>
#include <texture/loader.hpp>
#include <time/delta_time.hpp>

// Local C Libraries imports
extern "C" {
    #include <stb_image.h>
    #include <window/resize.h>
    #include <input/input.h>
}

// Constants
#define WIDTH 800
#define HEIGHT 600

int main(int argc, char **argv, char **env) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwSetErrorCallback([](int error, const char* description) {
        std::cerr << "GLFW Error (" << error << "): " << description << std::endl;
    });

    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Simple Window using OpenGL", nullptr, nullptr);
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
    Shader ourShader("./shaders/shader.vert", "./shaders/shader.frag");

    // Generating an array information needed for opengl
    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    stbi_set_flip_vertically_on_load(true);

    // Setting all 2D texture settings
    GLuint texture1 = loadTextureFromDisk("textures/container.jpg", GL_RGB);
    GLuint texture2 = loadTextureFromDisk("textures/awesomeface.png", GL_RGBA);

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

    // Loading textures
    ourShader.use();
    glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
    ourShader.setInt("texture2", 1);
    GLint visibility = glGetUniformLocation(ourShader.ID, "visibility");
    GLfloat visibilityValue = 0.2f;
    glUniform1f(visibility, visibilityValue);

    // Applying transformation
    unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");

    // 3D model
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    // Delta time
    Time time;

    enum RENDER_MODE render = FILL;
    char isKeyPressed = 0;
    // Program main loop
    while (!glfwWindowShouldClose(window)) {
        // Process input events
        processInput(window, &render, &isKeyPressed);

        time.Update();
        time.PrintDeltaTime(1.0f);

        // Exercise
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
            visibilityValue -= 0.5f * time.GetDeltaTime();
        }
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
            visibilityValue += 0.5f * time.GetDeltaTime();
        }
        glUniform1f(visibility, visibilityValue);

        // Clear Background
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Bind texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        // Render container
        ourShader.use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Move container around
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));


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
