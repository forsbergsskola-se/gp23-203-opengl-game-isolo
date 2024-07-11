#ifndef SHAPE_GENERATOR_H
#define SHAPE_GENERATOR_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "TriangleShader.h"
#include "Texture.h"
#include "CubeTexture.h"
#include "Camera.h"
#include "Window.h"
class ShapeGenerator 
{
public:
    ShapeGenerator();
    ~ShapeGenerator();
    void SetShape(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, bool includeTextureCoords);


    void Draw(Window& window, Camera& camera, Texture* texture=nullptr);

    void Transformation(const glm::vec3& position, float angle, const glm::vec3& axis, const glm::vec3& scale);

    void SetShapeColor(const glm::vec3& color);

    GLuint getVBO() const 
    {
        return ShapeVBO;
    }
private:

    Window& window;
    Camera& camera;
    void CheckGLError(const std::string& location);

    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    
    TriangleShader shapeShader;
    GLuint ShapeVBO;
    GLuint ShapeEBO;
    GLuint ShapeVAO;

    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 scale;
    glm::vec3 color;
};

#endif
