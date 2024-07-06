#ifndef SHAPE_GENERATOR_H
#define SHAPE_GENERATOR_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "TriangleShader.h"
#include "Texture.h"
#include "CubeTexture.h"

class ShapeGenerator 
{
public:
    ShapeGenerator();
    ~ShapeGenerator();

    void SetShape(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, bool includeTextureCoords);

    void SetCubeShape(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);


    void DrawCubemap(const glm::mat4& view, const glm::mat4& projection, TriangleShader& shader, CubeTexture& texture);

    void Draw(const glm::mat4& view, const glm::mat4& projection, TriangleShader& shader, Texture* texture = nullptr);

    void Transformation(const glm::vec3& position, float angle, const glm::vec3& axis, const glm::vec3& scale);

    void SetColor(const glm::vec3& color);

    void CheckGLError(const std::string& location);


    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    GLuint ShapeVBO;
    GLuint ShapeEBO;
    GLuint ShapeVAO;

    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 scale;
    glm::vec3 color;
};

#endif // SHAPE_GENERATOR_H
