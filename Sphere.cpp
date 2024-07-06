#include "Sphere.h"
#include <cmath>

Sphere::Sphere(float radius, int sectors, int stacks) {
    generateSphereVertices(radius, sectors, stacks);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Sphere::generateSphereVertices(float radius, int sectors, int stacks) {
    const float PI = 3.14159265359f;
    float sectorStep = 2 * PI / sectors;
    float stackStep = PI / stacks;
    float sectorAngle, stackAngle;
    float x, y, z;

    for (int i = 0; i <= stacks; ++i) {
        stackAngle = PI / 2 - i * stackStep;
        float xy = radius * cos(stackAngle);
        z = radius * sin(stackAngle);

        for (int j = 0; j <= sectors; ++j) {
            sectorAngle = j * sectorStep;
            x = xy * cos(sectorAngle);
            y = xy * sin(sectorAngle);
            vertices.push_back(glm::vec3(x, y, z));
        }
    }
}

void Sphere::Draw(Shader& shader) {
    shader.Activate();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, vertices.size());
    glBindVertexArray(0);
}
