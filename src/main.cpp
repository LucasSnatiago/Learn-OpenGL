// OpenGL imports
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Standard Libraries Imports
#include <iostream>

// Local C Libraries imports
extern "C" {
    #include <window/resize.h>
    #include <input/input.h>
}

// Vertex shader for the triangle
const char *vertexShaderSource = "#version 460 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSourceOrange = "#version 460 core\n"
    "out vec4 FragColor;\n"
    "void main() {\n"
    "FragColor = vec4(1.0f, 0.5f, 0.4f, 1.0f);\n"
    "}\0";

const char *fragmentShaderSourceYellow = "#version 460 core\n"
    "out vec4 FragColor;\n"
    "void main() {\n"
    "FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
    "}\0";


void checkShaderCompilationStatus(unsigned int shader) {
    // Checking for compilation status
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

int main(int argc, char **argv) {
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

    // Creating the vertex shading pipeline
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Checking for compilation error
    checkShaderCompilationStatus(vertexShader);

    // Creating the fragment shader pipeline
    unsigned int fragmentShaderOrange;
    fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderOrange, 1, &fragmentShaderSourceOrange, NULL);
    glCompileShader(fragmentShaderOrange);

    // Checking for compilation error
    checkShaderCompilationStatus(fragmentShaderOrange);

    // Creating the yellow color
    unsigned int fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderYellow, 1, &fragmentShaderSourceYellow, NULL);
    glCompileShader(fragmentShaderYellow);

    // Checking for compilation error
    checkShaderCompilationStatus(fragmentShaderYellow);

    // Shader program
    unsigned int shaderProgram[2];
    shaderProgram[0] = glCreateProgram();
    shaderProgram[1] = glCreateProgram();

    // Attaching shaders to the program
    glAttachShader(shaderProgram[0], vertexShader);
    glAttachShader(shaderProgram[1], vertexShader);
    glAttachShader(shaderProgram[0], fragmentShaderOrange);
    glAttachShader(shaderProgram[1], fragmentShaderYellow);
    glLinkProgram(shaderProgram[0]);
    glLinkProgram(shaderProgram[1]);
    // Check for linking errors
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram[0], GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram[0], 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glGetProgramiv(shaderProgram[1], GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram[1], 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }


    // Freeing shader from memory
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShaderYellow);
    glDeleteShader(fragmentShaderOrange);

    // Building the triangles
    float vertices1[] = {
         0.5f,  0.5f, 0.0f, // top right
         0.5f, -0.5f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
    };

    // Second triangle
    float vertices2[] = {
        0.95f, 0.95f, 0.0f, // Top right
        0.95f, 0.0f,  0.0f, // Bottom right
        0.55f, 0.0f, -0.5f  // Top Left
    };

    // Generating an array information needed for opengl
    unsigned int VBOs[2], VAOs[2];
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);

    // Setup for the first triangle
    // Bind Vertex Array Object
    glBindVertexArray(VAOs[0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

    // Interpreting my triangle
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Setup for the second triangle
    glBindVertexArray(VAOs[1]);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

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

        // Draw orange triangle
        glUseProgram(shaderProgram[0]);

        // First triangle
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Draw yellow triangle
        glUseProgram(shaderProgram[1]);

        // Draw second triangle
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Freeing all resources
    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);
    glDeleteProgram(shaderProgram[0]);
    glDeleteProgram(shaderProgram[1]);

    glfwTerminate();
    return 0;
}
