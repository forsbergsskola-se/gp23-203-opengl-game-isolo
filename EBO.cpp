#include "EBO.h"

// Constructor that generates an EBO and links it to indices
// The constructor takes a vector of indices and binds it to the EBO
EBO::EBO(std::vector<GLuint>& indices)
{
    // Generates a buffer ID for the EBO
    glGenBuffers(1, &ID);
    // Binds the EBO to the GL_ELEMENT_ARRAY_BUFFER target
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    // Allocates memory and initializes the buffer with the provided indices
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
}

// Function to bind the EBO
// Binds the EBO to make it active so that it can be used in rendering
void EBO::Bind()
{
    // Binds the EBO to the GL_ELEMENT_ARRAY_BUFFER target
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

// Function to unbind the EBO
// Unbinds the EBO to prevent accidental modifications
void EBO::Unbind()
{
    // Unbinds the current EBO by binding to 0
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// Function to delete the EBO
// Deletes the EBO from the GPU memory to free resources
void EBO::Delete()
{
    // Deletes the buffer with the given ID
    glDeleteBuffers(1, &ID);
}
