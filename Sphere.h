#pragma once

#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "shaderClass.h"

class Sphere {
public:
    unsigned int VAO, VBO;
    std::vector<glm::vec3> vertices;

    Sphere(float radius, int sectors, int stacks);
    void Draw(Shader& shader);
private:
    void generateSphereVertices(float radius, int sectors, int stacks);
};



