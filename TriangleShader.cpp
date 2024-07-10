#include "TriangleShader.h"
#include <fstream>
#include <sstream>
#include <iostream>

TriangleShader::TriangleShader(const char* vertexPath, const char* fragmentPath)
{
    std::string vertexCode = ReadShaderFile(vertexPath);
    std::string fragmentCode = ReadShaderFile(fragmentPath);

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vShaderCode, NULL);
    glCompileShader(vertexShader);
    CheckCompileErrors(vertexShader, "VERTEX");

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
    glCompileShader(fragmentShader);
    CheckCompileErrors(fragmentShader, "FRAGMENT");

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    CheckCompileErrors(shaderProgram, "PROGRAM");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    useTextureLocation = glGetUniformLocation(shaderProgram, "useTexture");
}

TriangleShader::~TriangleShader() 
{
    glDeleteProgram(shaderProgram);
}

void TriangleShader::Activate() const 
{
    glUseProgram(shaderProgram);
}
GLuint TriangleShader::GetUniformLocation(const std::string& name) const 
{
    return glGetUniformLocation(shaderProgram, name.c_str());
}

void TriangleShader::SetMat4(const std::string& name, const glm::mat4& mat) const {
    GLint location = glGetUniformLocation(shaderProgram, name.c_str());
    if (location == -1) {
        std::cerr << "Uniform " << name << " not found in shader program." << std::endl;
        return;
    }
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
    std::cout << "Set uniform: " << name << std::endl;
}

void TriangleShader::SetVec3(const std::string& name, const glm::vec3& value) const
{
    GLint location = GetUniformLocation(name);
    if (location != -1)
    {
        glUniform3fv(location, 1, glm::value_ptr(value));
        std::cout << "Set uniform " << name << " to vec3: (" << value.r << ", " << value.g << ", " << value.b << ")" << std::endl;
    }
    else
    {
        std::cerr << "Failed to set uniform " << name << " - location not found." << std::endl;
    }
}

void TriangleShader::SetColor(const std::string& name, const glm::vec3& color) 
{
    GLint location = GetUniformLocation(name);
    if (location != -1) 
    {
        glUniform3fv(location, 1, glm::value_ptr(color));
        std::cout << "Set uniform " << name << " to color: (" << color.r << ", " << color.g << ", " << color.b << ")" << std::endl;
    }
    else {
        std::cerr << "Failed to set uniform " << name << " - location not found." << std::endl;
    }
}

void TriangleShader::SetFloat(const std::string& name, float value) const 
{
    glUniform1f(GetUniformLocation(name), value);
}

void TriangleShader::SetInt(const std::string& name, GLint value)
{
    GLint location = glGetUniformLocation(shaderProgram, name.c_str());
    if (location != -1)
    {
        glUniform1i(location, value);
    }
    else
    {
        std::cerr << "Warning: Uniform " << name << " not found in shader!" << std::endl;
    }
}
void TriangleShader::SetBool(const std::string& name, bool value) 
{
    {
        GLuint location;
        if (name == "useTexture") 
        {
            location = useTextureLocation;
        }
        else if (name == "debugMode") 
        {
            location = debugModeLocation;
        }
        else 
        {
            location = GetUniformLocation(name);
        }
        glUniform1i(location, static_cast<int>(value));
    }
}

void TriangleShader::CheckCompileErrors(GLuint shader, std::string type) const 
{
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << std::endl;
        }
    }
    else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << std::endl;
        }
    }
}

std::string TriangleShader::ReadShaderFile(const char* shaderPath) const 
{
    std::string code;
    std::ifstream shaderFile;
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        shaderFile.open(shaderPath);
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
        code = shaderStream.str();
    }
    catch (std::ifstream::failure& e) {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << shaderPath << std::endl;
    }
    return code;
}
