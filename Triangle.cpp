/*
#include "Triangle.h"
#include "TriangleShader.h" // Include the TriangleShader header
#include "ElementBuffer.h"

Triangle::Triangle(const char* vertexPath, const char* fragmentPath) {
    shader = new TriangleShader(vertexPath, fragmentPath); // Initialize shader program
    setupVertices();
}

Triangle::~Triangle() {
    delete shader; // Clean up shader object
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
void Triangle::setupVertices() {
    vertices = {
        // Position            // Color
         0.0f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  // Top, red
        -0.5f, -0.5f, 0.5f,   0.0f, 1.0f, 0.0f,  // Bottom-left, green
         0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f,  // Bottom-right, blue
    };

    indices = {
        0, 1, 2  // Indices for a single triangle
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}
//Look for solution here.
void Triangle::Draw(glm::mat4 projection, glm::mat4 view, std::vector<glm::mat4>& models) {
    shader->Activate();

    glUniformMatrix4fv(shader->GetUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(shader->GetUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(view));

    glBindVertexArray(VAO);

    for (size_t i = 0; i < models.size(); ++i) {
        glUniformMatrix4fv(shader->GetUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(models[i]));
        glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, (void*)(i * 18 * sizeof(unsigned int)));
    }

    glBindVertexArray(0);
}
*/