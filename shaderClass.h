#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>   // OpenGL function pointers
#include <string>        // std::string
#include <fstream>       // std::ifstream
#include <sstream>       // std::stringstream
#include <iostream>      // std::cerr, std::endl
#include <cerrno>        // errno global variable

// Function prototype to read file contents
std::string get_file_contents(const char* filename);

class Shader
{
public:
    GLuint ID;  // Shader program ID

    // Constructor: reads and compiles shaders from files
    Shader(const char* vertexFile, const char* fragmentFile);

    // Activates the shader program for use
    void Activate();

    // Deletes the shader program
    void Delete();

private:
    // Private function to handle compilation errors
    void compileErrors(unsigned int shader, const char* type);
};

#endif
