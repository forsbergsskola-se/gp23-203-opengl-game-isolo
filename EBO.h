#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>
#include <vector>

class EBO
{
public:
    // Variable to store the ID of the Element Buffer Object
    GLuint ID;

    // Constructor that generates an EBO and links it to indices
    // The constructor takes a vector of indices and binds it to the EBO
    EBO(std::vector<GLuint>& indices);

    // Function to bind the EBO
    // Binds the EBO to make it active so that it can be used in rendering
    void Bind();

    // Function to unbind the EBO
    // Unbinds the EBO to prevent accidental modifications
    void Unbind();

    // Function to delete the EBO
    // Deletes the EBO from the GPU memory to free resources
    void Delete();
};

#endif
