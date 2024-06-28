#include "VAO.h"

// Constructor that generates a VAO ID
VAO::VAO()
{
    // Generate a VAO ID
    glGenVertexArrays(1, &ID);
}

// Links a VBO Attribute such as a position or color to the VAO
// VBO: the VBO containing the vertex data
// layout: the location of the attribute in the shader
// numComponents: the number of components (e.g., 3 for vec3)
// type: the data type of the attribute (e.g., GL_FLOAT)
// stride: the stride between consecutive attributes
// offset: the offset of the first component of the attribute
void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
    // Bind the VBO to ensure it is active
    VBO.Bind();
    // Configure the vertex attribute
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
    // Enable the vertex attribute
    glEnableVertexAttribArray(layout);
    // Unbind the VBO to prevent accidental modifications
    VBO.Unbind();
}

// Binds the VAO
void VAO::Bind()
{
    // Bind the VAO to make it the current vertex array
    glBindVertexArray(ID);
}

// Unbinds the VAO
void VAO::Unbind()
{
    // Unbind the VAO to prevent accidental modifications
    glBindVertexArray(0);
}

// Deletes the VAO
void VAO::Delete()
{
    // Delete the VAO to free up resources
    glDeleteVertexArrays(1, &ID);
}
