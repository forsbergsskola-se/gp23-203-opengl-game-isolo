#ifndef TRIANGLESHADER_H
#define TRIANGLESHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

class TriangleShader 
{
public:
    
    TriangleShader(const char* vertexPath, const char* fragmentPath);
    ~TriangleShader();

    void Activate() const;

    GLuint GetUniformLocation(const std::string& name) const;

    void SetMat4(const std::string& name, const glm::mat4& mat) const;

    void SetVec3(const std::string& name, const glm::vec3& value) const;

    void SetColor(const std::string& name, const glm::vec3& color);

    void SetFloat(const std::string& name, float value) const;

    void SetInt(const std::string& name, GLint value);

    void SetBool(const std::string& name, bool value);

    GLuint shaderProgram;
    GLuint ID;

private:
    
    void CheckCompileErrors(GLuint shader, std::string type) const;
    std::string ReadShaderFile(const char* shaderPath) const;

    GLuint useTextureLocation;
    GLuint debugModeLocation;
};

#endif // TRIANGLESHADER_H

