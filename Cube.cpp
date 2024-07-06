#include "Cube.h"
#include "Shader.h"

Cube::Cube() : CubeVAO(0), CubeVBO(0), CubeEBO(0) {}

Cube::~Cube() {
    glDeleteVertexArrays(1, &CubeVAO);
    glDeleteBuffers(1, &CubeVBO);
    glDeleteBuffers(1, &CubeEBO);
}

void Cube::CreateCube() {
    // Define vertices and indices for a cube
    vertices = {
        // Front face
        -0.5f, -0.5f,  0.5f,  // bottom-left
         0.5f, -0.5f,  0.5f,  // bottom-right
         0.5f,  0.5f,  0.5f,  // top-right
        -0.5f,  0.5f,  0.5f,  // top-left
        // Back face
        -0.5f, -0.5f, -0.5f,  // bottom-left
         0.5f, -0.5f, -0.5f,  // bottom-right
         0.5f,  0.5f, -0.5f,  // top-right
        -0.5f,  0.5f, -0.5f,  // top-left
    };

    indices = {
        // Front face
        0, 1, 2,
        2, 3, 0,
        // Right face
        1, 5, 6,
        6, 2, 1,
        // Back face
        7, 6, 5,
        5, 4, 7,
        // Left face
        4, 0, 3,
        3, 7, 4,
        // Bottom face
        4, 5, 1,
        1, 0, 4,
        // Top face
        3, 2, 6,
        6, 7, 3
    };

    // Setup buffers
    SetupMesh();
}

void Cube::Draw(const Shader& shader) {
    shader.Activate();
    glBindVertexArray(CubeVAO);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Cube::SetupMesh() {


    
   
}
