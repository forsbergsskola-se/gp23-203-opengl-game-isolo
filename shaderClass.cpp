#include "shaderClass.h"

// Function to read file contents into a string
std::string get_file_contents(const char* filename)
{
    std::ifstream in(filename, std::ios::binary); // File stream to read binary data
    if (in) // If file is successfully opened
    {
        std::string contents; // String to hold file contents
        in.seekg(0, std::ios::end); // Move file pointer to end
        contents.resize(in.tellg()); // Resize string to file size
        in.seekg(0, std::ios::beg); // Move file pointer to beginning
        in.read(&contents[0], contents.size()); // Read file into string
        in.close(); // Close file stream
        return contents; // Return file contents as string
    }
    throw(errno); // Throw an error if file could not be opened
}

// Constructor: reads and compiles vertex and fragment shaders
Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
    std::string vertexCode = get_file_contents(vertexFile); // Read vertex shader source
    std::string fragmentCode = get_file_contents(fragmentFile); // Read fragment shader source

    const char* vertexSource = vertexCode.c_str(); // Convert vertex shader source to C-string
    const char* fragmentSource = fragmentCode.c_str(); // Convert fragment shader source to C-string

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); // Create vertex shader object
    glShaderSource(vertexShader, 1, &vertexSource, NULL); // Attach vertex shader source
    glCompileShader(vertexShader); // Compile vertex shader
    compileErrors(vertexShader, "VERTEX"); // Check and log compilation errors

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // Create fragment shader object
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL); // Attach fragment shader source
    glCompileShader(fragmentShader); // Compile fragment shader
    compileErrors(fragmentShader, "FRAGMENT"); // Check and log compilation errors

    ID = glCreateProgram(); // Create shader program
    glAttachShader(ID, vertexShader); // Attach vertex shader to program
    glAttachShader(ID, fragmentShader); // Attach fragment shader to program
    glLinkProgram(ID); // Link shaders into program
    compileErrors(ID, "PROGRAM"); // Check and log linking errors

    glDeleteShader(vertexShader); // Delete vertex shader (no longer needed after linking)
    glDeleteShader(fragmentShader); // Delete fragment shader (no longer needed after linking)
}

// Activate the shader program for use
void Shader::Activate()
{
    glUseProgram(ID); // Use the shader program for rendering
}

// Delete (clean up) the shader program
void Shader::Delete()
{
    glDeleteProgram(ID); // Delete the shader program and associated resources
}

// Private function to handle compilation and linking errors
void Shader::compileErrors(unsigned int shader, const char* type)
{
    GLint hasCompiled; // Variable to store compilation status
    char infoLog[1024]; // Buffer to store error message

    if (type != "PROGRAM") // If handling shader compilation errors
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled); // Get compilation status
        if (hasCompiled == GL_FALSE) // If compilation failed
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog); // Get compilation error message
            std::cout << "SHADER_COMPILATION_ERROR for: " << type << "\n" << infoLog << std::endl; // Print error message
        }
    }
    else // If handling shader program linking errors
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled); // Get linking status
        if (hasCompiled == GL_FALSE) // If linking failed
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog); // Get linking error message
            std::cout << "SHADER_LINKING_ERROR for: " << type << "\n" << infoLog << std::endl; // Print error message
        }
    }
}
