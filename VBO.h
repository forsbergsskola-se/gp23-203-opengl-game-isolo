#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <vector>

// Vertex structure defining position, normal, color, and texture coordinates
struct Vertex
{
    glm::vec3 position; // Position of the vertex in 3D space
    glm::vec3 normal;   // Normal vector of the vertex
    glm::vec3 color;    // Color of the vertex
    glm::vec2 texUV;    // Texture coordinates of the vertex
};

// Vertex Buffer Object (VBO) class
class VBO
{
public:
    GLuint ID; // ID/handle of the VBO

    // Constructor: generates a VBO and fills it with vertex data
    VBO(std::vector<Vertex>& vertices);

    // Binds the VBO to the GL_ARRAY_BUFFER target
    void Bind();

    // Unbinds any buffer object from the GL_ARRAY_BUFFER target
    void Unbind();

    // Deletes the VBO by deallocating its buffer object
    void Delete();
};

#endif
