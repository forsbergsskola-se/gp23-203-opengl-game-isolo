#include "SphereGenerator.h"
#include <glm/gtc/constants.hpp>

Sphere GenerateSphere(float radius, unsigned int rings, unsigned int sectors) {
    Sphere sphere;
    float const R = 1.0f / (float)(rings - 1);
    float const S = 1.0f / (float)(sectors - 1);
    int r, s;

    sphere.vertices.resize(rings * sectors);
    sphere.indices.resize(rings * sectors * 6);

    std::vector<glm::vec3>::iterator v = sphere.vertices.begin();
    std::vector<unsigned int>::iterator i = sphere.indices.begin();
    for (r = 0; r < rings; r++) {
        for (s = 0; s < sectors; s++) {
            float const y = sin(-glm::pi<float>() / 2 + glm::pi<float>() * r * R);
            float const x = cos(2 * glm::pi<float>() * s * S) * sin(glm::pi<float>() * r * R);
            float const z = sin(2 * glm::pi<float>() * s * S) * sin(glm::pi<float>() * r * R);

            *v++ = glm::vec3(x, y, z) * radius;
            *i++ = r * sectors + s;
            *i++ = r * sectors + (s + 1);
            *i++ = (r + 1) * sectors + (s + 1);
            *i++ = (r + 1) * sectors + s;
        }
    }

    return sphere;
}
