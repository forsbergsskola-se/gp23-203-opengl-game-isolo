
#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <glad/glad.h>          // OpenGL headers
#include <stb/stb_image.h>      // STB image library for image loading

#include "TriangleShader.h"        // Shader class header

class Texture
{
public:
    GLuint ID;                  // Texture ID in OpenGL
    GLuint type;           // Type of texture (e.g., "diffuse", "specular")

    // Constructor to initialize the texture
    Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

    // Function to bind the texture to a specific texture unit in the shader
    void SetTextureUnit(TriangleShader& shader, const char* uniform, GLuint unit);

    // Function to bind the texture
    void Bind();

    // Function to unbind the texture
    void Unbind();

    // Function to delete (clean up) the texture
    void Delete();
};

#endif // TEXTURE_CLASS_H