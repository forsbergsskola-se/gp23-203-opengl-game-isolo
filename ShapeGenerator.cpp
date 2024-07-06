#include "ShapeGenerator.h"
#include <iostream>
#include <glad/glad.h>
#include <glm/gtx/quaternion.hpp>

ShapeGenerator::ShapeGenerator()
    : ShapeVBO(0), ShapeEBO(0), ShapeVAO(0), position(glm::vec3(0.0f)), rotation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)), scale(glm::vec3(1.0f)), color(glm::vec3(0.1f)) {}

ShapeGenerator::~ShapeGenerator() 
{   
    std::cout << "ShapeGenerator Getting Destroyed..." << std::endl;
    glDeleteVertexArrays(1, &ShapeVAO);
    std::cout << "ShapeGenerator 1..." << std::endl;

    glDeleteBuffers(1, &ShapeVBO);
    std::cout << "ShapeGenerator 2..." << std::endl;

    glDeleteBuffers(1, &ShapeEBO);

    std::cout << "ShapeGenerator is Destroyed..." << std::endl;

}

void ShapeGenerator::SetShape(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, bool includeTextureCoords) 
{
    this->vertices = vertices;
    this->indices = indices;


    // Generate buffers
    glGenVertexArrays(1, &ShapeVAO);
    ShapeGenerator::CheckGLError("ShapeGenerator::SetShape - glGenVertexArrays");

    glGenBuffers(1, &ShapeVBO);
    CheckGLError("ShapeGenerator::SetShape - glGenBuffers (VBO)");

    glGenBuffers(1, &ShapeEBO);
    CheckGLError("ShapeGenerator::SetShape - glGenBuffers (EBO)");

    // Bind VAO
    glBindVertexArray(ShapeVAO);
    CheckGLError("ShapeGenerator::SetShape - glBindVertexArray");

    // Bind VBO and set data
    glBindBuffer(GL_ARRAY_BUFFER, ShapeVBO);
    CheckGLError("ShapeGenerator::SetShape - glBindBuffer (VBO)");
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    CheckGLError("ShapeGenerator::SetShape - glBufferData (VBO)");

    // Bind EBO and set data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ShapeEBO);
    CheckGLError("ShapeGenerator::SetShape - glBindBuffer (EBO)");
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    CheckGLError("ShapeGenerator::SetShape - glBufferData (EBO)");

    // Set vertex attribute pointers
    if (includeTextureCoords) 
    {
        // Position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        CheckGLError("ShapeGenerator::SetShape - glVertexAttribPointer (position)");
        glEnableVertexAttribArray(0);
        CheckGLError("ShapeGenerator::SetShape - glEnableVertexAttribArray (position)");

        // Texture coordinate attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        CheckGLError("ShapeGenerator::SetShape - glVertexAttribPointer (texCoords)");
        glEnableVertexAttribArray(1);
        CheckGLError("ShapeGenerator::SetShape - glEnableVertexAttribArray (texCoords)");
    }
    else 
    {
        // Position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        CheckGLError("ShapeGenerator::SetShape - glVertexAttribPointer (position)");
        glEnableVertexAttribArray(0);
        CheckGLError("ShapeGenerator::SetShape - glEnableVertexAttribArray (position)");
    }

    // Unbind VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    CheckGLError("ShapeGenerator::SetShape - glBindBuffer (0) and glBindVertexArray (0)");

    std::cout << "Shape set successfully." << std::endl;
}

void ShapeGenerator::SetCubeShape(const std::vector<float>& vertices, const std::vector<unsigned int>& indices) 
{
    this->vertices = vertices;
    this->indices = indices;

    glGenVertexArrays(1, &ShapeVAO);
    glGenBuffers(1, &ShapeVBO);
    glGenBuffers(1, &ShapeEBO);

    glBindVertexArray(ShapeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, ShapeVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ShapeEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);  
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

}

void ShapeGenerator::DrawCubemap(const glm::mat4& view, const glm::mat4& projection, TriangleShader& shader, CubeTexture& texture) 
{
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
    modelMatrix *= glm::toMat4(rotation);
    modelMatrix = glm::scale(modelMatrix, scale);

    glm::mat4 MVP = projection * view * modelMatrix;

    shader.Activate();
    shader.SetMat4("model", modelMatrix);
    shader.SetMat4("view", view);
    shader.SetMat4("projection", projection);
    shader.SetMat4("MVP", MVP);

    texture.Bind();
    shader.SetInt("skybox", 0);

    glBindVertexArray(ShapeVAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);

    texture.Unbind();
}

void ShapeGenerator::Draw(const glm::mat4& view, const glm::mat4& projection, TriangleShader& shader, Texture* texture) 
{
    glm::mat4 modelMatrix = glm::mat4(1.0f);

    modelMatrix = glm::translate(modelMatrix, position);
    modelMatrix *= glm::toMat4(rotation);
    modelMatrix = glm::scale(modelMatrix, scale);

    glm::mat4 MVP = projection * view * modelMatrix;

    shader.Activate();
    shader.SetMat4("model", modelMatrix);
    shader.SetMat4("view", view);
    shader.SetMat4("projection", projection);
    shader.SetMat4("MVP", MVP);
    shader.SetVec3("ourColor", color);

    if (texture) 
    {
        texture->Bind();
        shader.SetBool("useTexture", true);
    }
    else {
        shader.SetBool("useTexture", false);
    }

    glBindVertexArray(ShapeVAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);

    if (texture) {
        texture->Unbind();
    }
}

void ShapeGenerator::Transformation(const glm::vec3& position, float angle, const glm::vec3& axis, const glm::vec3& scale) {
    this->position = position;
    this->rotation = glm::angleAxis(glm::radians(angle), glm::normalize(axis));
    this->scale = scale;
}

void ShapeGenerator::SetColor(const glm::vec3& color) {
    this->color = color;
}

void ShapeGenerator::CheckGLError(const std::string& location) {
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error at " << location << ": " << err << std::endl;
    }
}
