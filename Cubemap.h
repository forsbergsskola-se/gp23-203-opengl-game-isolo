#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "TriangleShader.h" 
#include "Window.h"
#include "Camera.h"
#include "ShapeDefiner.h"
#include "CubeTexture.h"
class Cubemap
{
public:

    Cubemap();
    void SetCubeShape(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);

    void DrawCubemap(Window& window, Camera& camera, CubeTexture& texture);

    void Transformation(const glm::vec3& position, float angle, const glm::vec3& axis, const glm::vec3& scale);

    ~Cubemap();
     

private:

    CubeTexture& texture;

    std::vector<float> cubemapVertices;
    std::vector<unsigned int> cubemapIndices;

    GLuint CubemapVAO;
    GLuint CubemapVBO;
    GLuint CubemapEBO;
   
    Window& window;
    Camera& camera;

    TriangleShader cubemapShader;

    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 scale;

    void CheckGLCubeError(const std::string& where);

};
