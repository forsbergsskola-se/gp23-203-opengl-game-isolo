#include "ShapeGenerator.h"
#include <iostream>
#include <glad/glad.h>
#include <glm/gtx/quaternion.hpp>
#include "Light.h"

ShapeGenerator::ShapeGenerator()
    : ShapeVBO(0), ShapeEBO(0), ShapeVAO(0), position(glm::vec3(0.0f)), rotation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)),
    scale(glm::vec3(1.0f)), color(glm::vec3(1.0f)), lightColor(glm::vec3(1.0f)), lightPos(glm::vec3(1.0f)), shapeShader("triangle.vert", "triangle.frag"), window(window), camera(camera) {}

ShapeGenerator::~ShapeGenerator()
{
    glDeleteVertexArrays(1, &ShapeVAO);

    glDeleteBuffers(1, &ShapeVBO);

    glDeleteBuffers(1, &ShapeEBO);


}
void ShapeGenerator::SetShape(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, bool includeTextureCoords)
{
    this->vertices = vertices;
    this->indices = indices;


    // Generate buffers
    glGenVertexArrays(1, &ShapeVAO);

    glGenBuffers(1, &ShapeVBO);

    glGenBuffers(1, &ShapeEBO);

    // Bind VAO
    glBindVertexArray(ShapeVAO);

    // Bind VBO and set data
    glBindBuffer(GL_ARRAY_BUFFER, ShapeVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ShapeEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    if (includeTextureCoords) {
        // Position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // Texture coordinate attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
    }
    else {
        // Position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }

    // Unbind VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}

void ShapeGenerator::Draw(Window& window, Camera& camera, Texture* texture)
{

    glm::mat4 modelMatrix = glm::mat4(1.0f);

    modelMatrix = glm::translate(modelMatrix, position);
    modelMatrix *= glm::toMat4(rotation);
    modelMatrix = glm::scale(modelMatrix, scale);

    float aspectRatio = static_cast<float>(window.getWidth()) / static_cast<float>(window.getHeight());

    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = camera.GetProjectionMatrix(aspectRatio);

    glm::mat4 MVP = projection * view * modelMatrix;

    // Activate the shader program
    shapeShader.Activate();

    // Set uniforms in the shader
    shapeShader.SetMat4("objectMVP", MVP);
    shapeShader.SetColor("ourColor", color);

    // Set light properties
    shapeShader.SetVec3("lightPos", lightPos);

    glm::vec3 lightDirection = glm::normalize(glm::vec3(10.0f, 3.0f, -3.5f));
    shapeShader.SetVec3("lightDirection", lightDirection);

    float specularStrength = 0.50f;
    shapeShader.SetFloat("specularStrength", specularStrength);

    float shininess = 10.0f; // Example shininess value
    shapeShader.SetFloat("shininess", shininess);

    lightColor = glm::vec3(1.0f, 1.0f, 1.0f); // Example light color
    shapeShader.SetColor("lightColor", lightColor);

    float emissiveLighting = 1.0f;
    shapeShader.SetFloat("emissiveStrenght", emissiveLighting);


    CheckGLError(" ourColor uniform");

    if (texture)
    {
        texture->Bind();
        shapeShader.SetBool("useTexture", true);
    }
    else
    {
        shapeShader.SetBool("useTexture", false);
    }

    glBindVertexArray(ShapeVAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);

    if (texture)
    {
        texture->Unbind();
    }

}
void ShapeGenerator::Transformation(const glm::vec3& position, float angle, const glm::vec3& axis, const glm::vec3& scale) {
    this->position = position;
    this->rotation = glm::angleAxis(glm::radians(angle), glm::normalize(axis));
    this->scale = scale;
}

void ShapeGenerator::SetShapeColor(const glm::vec3& color)
{
    this->color = color;
}
void ShapeGenerator::SetLightColor(const glm::vec3& lightColor)
{
    this->lightColor = lightColor;
}

void ShapeGenerator::SetLightPos(const glm::vec3& lightPos)
{
    this->lightPos = lightPos;
}

void ShapeGenerator::CheckGLError(const std::string& location)
{
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR)
    {
        std::cerr << "OpenGL error at " << location << ": " << err << std::endl;
    }
}
