/*
#include <vector>
#include <string>
#include "TriangleShader.h"
#include "Camera.h"
#include <stb/stb_image.h>

class Skybox 
{
public:

    Skybox();

    ~Skybox();

    void SetSkybox();
    void DrawSkybox(const glm::mat4& view, const glm::mat4& projection, TriangleShader &shader);
    void Destroy();

    void CheckSkyboxGLError(const std::string& location);

   
private:


    GLuint SkyboxVAO;
    GLuint SkyboxVBO;
    GLuint SkyboxEBO;
    GLuint CubeVAO;
    GLuint CubeVBO;
    GLuint CubeEBO;

    TriangleShader shader;
    
    std::vector<std::string> skyboxFaces;

    GLuint skyTextureID;
  

    void LoadCubemap(const std::vector<std::string>& faces, GLuint& textureID);
};

*/