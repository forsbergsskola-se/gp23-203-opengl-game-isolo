#include "Cubemap.h"
#include <stb/stb_image.h>
#include <GLFW/glfw3.h>

Cubemap::Cubemap()
    :
    position(glm::vec3(0.0f)), rotation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)),
    scale(glm::vec3(1.0f)),
    cubemapShader("cubemap.vert", "cubemaps.frag"),
    CubemapVAO(0),
    CubemapVBO(0),
    CubemapEBO(0),
    texture(texture),
    window(window),
    camera(camera)
{}
Cubemap::~Cubemap()
{
    glDeleteVertexArrays(1, &CubemapVAO);
    glDeleteBuffers(1, &CubemapVBO);
    glDeleteBuffers(1, &CubemapEBO);
}
void Cubemap::SetCubeShape(const std::vector<float>& vertices, const std::vector<unsigned int>& indices)
{
    this->cubemapVertices = cubemapVertices;
    this->cubemapIndices = cubemapIndices;

    glGenVertexArrays(1, &CubemapVAO);
    CheckGLCubeError("SetCubeShape->1");
    glGenBuffers(1, &CubemapVBO);
    CheckGLCubeError("SetCubeShape->2");

    glGenBuffers(1, &CubemapEBO);
    CheckGLCubeError("SetCubeShape->3");

    glBindVertexArray(CubemapVAO);

    CheckGLCubeError("SetCubeShape->4");

    glBindBuffer(GL_ARRAY_BUFFER, CubemapVBO);

    glBufferData(GL_ARRAY_BUFFER, cubemapVertices.size() * sizeof(float), cubemapVertices.data(), GL_STATIC_DRAW);
    CheckGLCubeError("SetCubeShape->5");

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, CubemapEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, cubemapIndices.size() * sizeof(unsigned int), cubemapIndices.data(), GL_STATIC_DRAW);
    CheckGLCubeError("SetCubeShape->6");


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    CheckGLCubeError("Cubemap::Setup");
}

void Cubemap::DrawCubemap(Window& window, Camera& camera, CubeTexture& texture)
{
    glm::mat4 modelMatrix = glm::mat4(1.0f);

    modelMatrix = glm::translate(modelMatrix, position);
    modelMatrix *= glm::toMat4(rotation);
    modelMatrix = glm::scale(modelMatrix, scale);

    float aspectRatio = static_cast<float>(window.getWidth()) / static_cast<float>(window.getHeight());

    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = camera.GetProjectionMatrix(aspectRatio);

    glm::mat4 cubeMVP = projection * view * modelMatrix;

    cubemapShader.Activate();

    cubemapShader.SetMat4("cubeMVP", cubeMVP);

    texture.Bind();
    cubemapShader.SetInt("cubemap", 0);

    glBindVertexArray(CubemapVAO);
    glDrawElements(GL_TRIANGLES, cubemapIndices.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);

    texture.Unbind();
    CheckGLCubeError("Cubemap Draw");
}
void Cubemap::Transformation(const glm::vec3& position, float angle, const glm::vec3& axis, const glm::vec3& scale) {
    this->position = position;
    this->rotation = glm::angleAxis(glm::radians(angle), glm::normalize(axis));
    this->scale = scale;
}
void Cubemap::CheckGLCubeError(const std::string& where)
{
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR)
    {
        std::cerr << "OpenGL error in " << where << ": " << err << std::endl;
    }
}
