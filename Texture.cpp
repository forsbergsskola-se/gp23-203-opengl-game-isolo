#include "Texture.h"
#include <stdexcept>
#include <iostream>

// Constructor: loads an image file and creates a texture
Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
    std::cout << "Initializing Texture with image: " << image << std::endl;
    // Assigns the type of the texture to the texture object
    type = texType;

    // Stores the width, height, and the number of color channels of the image
    int widthImg, heightImg, numColCh;
    // Flips the image so it appears right side up
    stbi_set_flip_vertically_on_load(true);
    // Reads the image from a file and stores it in bytes
    unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 4);

    if (!bytes)
    {
        std::cerr << "Failed to load texture: " << image << std::endl;
    }
    // Generates an OpenGL texture object
    glGenTextures(1, &ID);
    // Assigns the texture to a Texture Unit
    glActiveTexture(slot);
    glBindTexture(texType, ID);
    std::cout << "Generated texture ID: " << ID << std::endl;

    // Configures the type of algorithm that is used to make the image smaller or bigger
    glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR); //Option 1; GL_NEAREST  Option 2; GL_NEAREST_MIPMAP_LINEAR
    glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR); //Option 1; GL_NEAREST  Option 2; GL_NEAREST_MIPMAP_LINEAR
    // Configures the way the texture repeats (if it does at all)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //Option 1; GL_REPEAT  Option 2; GL_CLAMP_TO_EDGE
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    std::cout << "Setting texture parameters" << std::endl;



    glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
    std::cout << "Texture data loaded to GPU" << std::endl;

    glGenerateMipmap(texType);
    std::cout << "Mipmap generated" << std::endl;

    stbi_image_free(bytes);
    glBindTexture(texType, 0);
    std::cout << "Texture initialization complete for image: " << image << std::endl;

}

// Sets the texture unit for a shader uniform
void Texture::SetTextureUnit(TriangleShader& shader, const char* uniform, GLuint unit)
{
    std::cout << "Setting texture unit for uniform: " << uniform << " to unit: " << unit << std::endl;
    // Gets the location of the uniform
    GLuint texUni = glGetUniformLocation(shader.shaderProgram, uniform);
    // Shader needs to be activated before changing the value of a uniform
    shader.Activate();
    // Sets the value of the uniform
    glUniform1i(texUni, unit);
}

// Binds the texture
void Texture::Bind()
{
    std::cout << "Binding texture ID: " << ID << std::endl;
    glBindTexture(type, ID);
}

// Unbinds the texture
void Texture::Unbind()
{
    std::cout << "Unbinding texture" << std::endl;
    glBindTexture(type, 0);
}

// Deletes the texture
void Texture::Delete()
{
    std::cout << "Deleting texture ID: " << ID << std::endl;
    glDeleteTextures(1, &ID);
}