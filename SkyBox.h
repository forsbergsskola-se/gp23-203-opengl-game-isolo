#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "TriangleShader.h" 
#include "Window.h"
#include "Camera.h"
#include "CubeTexture.h"

class Skybox
{
public:


    Skybox();
    void SetSkybox(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);

    void DrawSkybox(Window& window, Camera& camera, CubeTexture* useSkyTexture = nullptr);

    ~Skybox();
    GLuint SkyboxVAO;
    GLuint SkyboxVBO;
    GLuint SkyboxEBO;

private:

    std::vector<float> skyboxVertices;
    std::vector<unsigned int> skyboxIndices;

    Window& window;
    Camera& camera;
    CubeTexture* useSkyTexture;

    TriangleShader skyboxShader;

    void CheckGLError(const std::string& where);

};
