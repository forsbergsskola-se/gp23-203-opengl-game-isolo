#ifndef VAO_H
#define VAO_H

#include <glad/glad.h>

class VAO {
public:
    VAO();
    ~VAO();
    void Bind();
    void Unbind();
private:
    GLuint id;
};

#endif
