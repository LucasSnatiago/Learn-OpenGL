#include <glad/gl.h>
#include <stb_image.h>
#include <iostream>

static const inline void _defaultTextureFilters() {
    // Texture will be mirrored on the edges of the screen
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    // Texture filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

GLuint loadTextureFromDisk(const char* path, uint32_t rgb_type) {
    GLuint texture;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    _defaultTextureFilters();

    // Loading textures
    GLsizei width, height, nrChannels;
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);

    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, rgb_type, width, height, 0, rgb_type, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

    } else {
        std::cerr << "Failed to load texture from disk\n";
        std::exit(EXIT_FAILURE);

    }

    // Freeing image from RAM, keeping it in OpenGL driver only
    stbi_image_free(data);

    return texture;
}
