#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include "TriangleShader.h"

class CubeTexture 
{
public:

    GLuint textureID;

    // Constructor: loads six images and creates a cube map texture
    CubeTexture(std::vector<std::string>& faces);

    void LoadCubeTextures(std::vector<std::string>& faces);


    void SetCubeTextureUnit(TriangleShader& shader, const char* uniform, GLuint unit);

    std::vector<std::string> currentFaces;

    // Bind the cube map texture to a specific texture unit
    void Bind();

    // Unbind the cube map texture
    void Unbind();

    // Delete the cube map texture
    void Delete();
};

