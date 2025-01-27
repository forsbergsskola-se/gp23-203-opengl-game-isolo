#pragma once
#include <glad/glad.h>
#include "ShapeGenerator.h"
#include "TriangleShader.h"

class Light
{
public:
    Light();
    ~Light();
    void LightShape(const std::vector<float>& lightSourceVertices, const std::vector<unsigned int>& indices);

    void LightOn(Window& window, Camera& camera, bool showLightSource);

    void SetPositionAndColor(TriangleShader& lightShader, const glm::vec3& lightPos, const glm::vec3& lightColor);

    void SetScale(const glm::vec3& scale);

    void CheckGLError(const std::string& location);


private:


    glm::vec3 lightSourceColor;
    glm::vec3 lightPos;


    glm::quat rotation;
    glm::vec3 scale;

    GLuint lightSourceVBO;
    GLuint lightSourceVAO;
    GLuint lightSourceEBO;


    std::vector<float> lightSourceVertices;
    std::vector<unsigned int> lightSourceIndices;

    TriangleShader lightSourceShader;

    TriangleShader& lightShader;
    Window& window;
    Camera& camera;
};
