#ifndef SPHERE_GENERATOR_H
#define SPHERE_GENERATOR_H

#include <vector>
#include <glm/glm.hpp>

struct Sphere {
    std::vector<glm::vec3> vertices;
    std::vector<unsigned int> indices;
};

Sphere GenerateSphere(float radius, unsigned int rings, unsigned int sectors);

#endif 
