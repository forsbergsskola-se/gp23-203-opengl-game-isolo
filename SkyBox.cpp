#include "Skybox.h"
#include <stb/stb_image.h>
#include <GLFW/glfw3.h>
#include "CubeTexture.h"

Skybox::Skybox()
    :
    skyboxShader("skybox.vert", "skybox.frag"),
    SkyboxVAO(0),
    SkyboxVBO(0),
    SkyboxEBO(0),
    window(window),
    camera(camera),
    useSkyTexture(useSkyTexture)
{}
void Skybox::SetSkybox(const std::vector<float>& vertices, const std::vector<unsigned int>& indices)
{
    this->skyboxVertices = vertices;
    this->skyboxIndices = indices;

    glGenVertexArrays(1, &SkyboxVAO);

    glGenBuffers(1, &SkyboxVBO);

    glGenBuffers(1, &SkyboxEBO);

    glBindVertexArray(SkyboxVAO);


    glBindBuffer(GL_ARRAY_BUFFER, SkyboxVBO);

    glBufferData(GL_ARRAY_BUFFER, skyboxVertices.size() * sizeof(float), skyboxVertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, SkyboxEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, skyboxIndices.size() * sizeof(unsigned int), skyboxIndices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

}

void Skybox::DrawSkybox(Window& window, Camera& camera, CubeTexture* useSkyTexture)
{
    float aspectRatio = static_cast<float>(window.getWidth()) / static_cast<float>(window.getHeight());

    glm::mat4 skyView = glm::mat4(glm::mat3(camera.GetViewMatrix()));
    glm::mat4 skyProjection = camera.GetProjectionMatrix(aspectRatio);

    glDepthMask(GL_FALSE);
    float timeValue = glfwGetTime();

    std::cout << "Activating Triangle Shader in Skybox.." << std::endl;
    skyboxShader.Activate();

    skyboxShader.SetMat4("skyView", skyView);
    skyboxShader.SetMat4("skyProjection", skyProjection);

    skyboxShader.SetFloat("time", timeValue);


    if (useSkyTexture)
    {
        useSkyTexture->Bind();
        skyboxShader.SetBool("useSkyTexture", true);
    }
    else
    {
        skyboxShader.SetBool("useSkyTexture", false);

    }
    skyboxShader.SetInt("skybox", 0);

    glBindVertexArray(SkyboxVAO);
    glDrawElements(GL_TRIANGLES, skyboxIndices.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);

    if (useSkyTexture)
    {
        useSkyTexture->Unbind();
    }

    glDepthMask(GL_TRUE);

}
Skybox::~Skybox()
{
    glDeleteVertexArrays(1, &SkyboxVAO);
    glDeleteBuffers(1, &SkyboxVBO);
    glDeleteBuffers(1, &SkyboxEBO);

    CheckGLError("Error in skybox destructor, figure out why");
}
void Skybox::CheckGLError(const std::string& where)
{
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR)
    {
        std::cerr << "OpenGL error in " << where << ": " << err << std::endl;
    }
}