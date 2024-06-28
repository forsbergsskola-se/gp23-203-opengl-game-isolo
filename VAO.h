#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>
#include "VBO.h"

// VAO (Vertex Array Object) class
class VAO
{
public:
    // ID reference for the Vertex Array Object
    GLuint ID;

    // Constructor that generates a VAO ID
    VAO();

    // Links a VBO Attribute such as a position or color to the VAO
    // VBO: the VBO containing the vertex data
    // layout: the location of the attribute in the shader
    // numComponents: the number of components (e.g., 3 for vec3)
    // type: the data type of the attribute (e.g., GL_FLOAT)
    // stride: the stride between consecutive attributes
    // offset: the offset of the first component of the attribute
    void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);

    // Binds the VAO
    void Bind();

    // Unbinds the VAO
    void Unbind();

    // Deletes the VAO
    void Delete();
};

#endif
