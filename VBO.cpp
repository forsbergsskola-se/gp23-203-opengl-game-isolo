#include "VBO.h"

// Constructor: Generates a VBO and fills it with vertex data
VBO::VBO(std::vector<Vertex>& vertices)
{
    glGenBuffers(1, &ID);                           // Generate 1 buffer object handle
    glBindBuffer(GL_ARRAY_BUFFER, ID);               // Bind buffer to GL_ARRAY_BUFFER target
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);                   // Usage pattern hint: data will not change
}

// Binds the VBO to the GL_ARRAY_BUFFER target
void VBO::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, ID);  // Bind this VBO to GL_ARRAY_BUFFER
}

// Unbinds any buffer object from the GL_ARRAY_BUFFER target
void VBO::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);   // Unbind any buffer from GL_ARRAY_BUFFER
}

// Deletes the VBO by deallocating its buffer object
void VBO::Delete()
{
    glDeleteBuffers(1, &ID);            // Delete 1 buffer object identified by ID
}
