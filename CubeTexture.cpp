#include "CubeTexture.h"
CubeTexture::CubeTexture(const std::vector<std::string>& faces)
{
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, numChannels;
    for (unsigned int i = 0; i < faces.size(); ++i) 
    {
        stbi_set_flip_vertically_on_load(false); 
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &numChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
            std::cerr << "Cube map texture loaded: " << faces[i] << std::endl;
        }
        else {
            std::cerr << "Failed to load cube map texture: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void CubeTexture::SetCubeTextureUnit(TriangleShader& shader, const char* uniform, GLuint unit)
{
    GLuint texUni = glGetUniformLocation(shader.shaderProgram, uniform);
    shader.Activate();
    glUniform1i(texUni, unit);
}

void CubeTexture::Bind()
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
}

void CubeTexture::Unbind()
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void CubeTexture::Delete()
{
    glDeleteTextures(1, &textureID);
}