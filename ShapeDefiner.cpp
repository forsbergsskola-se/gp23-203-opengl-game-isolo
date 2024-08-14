#include "ShapeDefiner.h"
#include <vector>
#include <cmath>
#include <glm/ext/scalar_constants.hpp>
# define M_PI           3.14159265358979323846





std::vector<float> ShapeDefiner::GetTriangleVertices(bool texCoordWanted)
{
    std::vector<float> vertices;

    float radius = 0.5f; // Radius of the rounding (half the triangle size)
    int numSegments = 10; // Number of segments to approximate the curve

    // Central vertex
    vertices.push_back(0.0f);
    vertices.push_back(0.5f); // Top of the triangle
    vertices.push_back(0.0f); // Z-coordinate (assuming 2D triangle)
    vertices.push_back(0.0f); // Normal X
    vertices.push_back(0.0f); // Normal Y
    vertices.push_back(1.0f); // Normal Z

    if (texCoordWanted) {
        vertices.push_back(0.5f); // Texture coordinate U
        vertices.push_back(1.0f); // Texture coordinate V
    }

    // Calculate points on the circle to form the rounded edge
    for (int i = 0; i <= numSegments; ++i) {
        float angle = static_cast<float>(i) / static_cast<float>(numSegments) * 2.0f * M_PI;
        float x = radius * std::cos(angle);
        float y = radius * std::sin(angle);

        // Add vertex positions
        vertices.push_back(x);
        vertices.push_back(y); // Y-coordinate along the curve
        vertices.push_back(0.0f); // Z-coordinate (assuming 2D triangle)

        // Calculate normal for the curved edge (tangent approximation)
        float tangentX = -std::sin(angle);
        float tangentY = std::cos(angle);
        vertices.push_back(tangentX); // Normal X
        vertices.push_back(tangentY); // Normal Y
        vertices.push_back(0.0f); // Normal Z

        if (texCoordWanted) {
            vertices.push_back(x * 0.5f + 0.5f); // Texture coordinate U
            vertices.push_back(y * 0.5f + 0.5f); // Texture coordinate V
        }
    }

    return vertices;
}

std::vector<unsigned int> ShapeDefiner::GetTriangleIndices()
{
    std::vector<unsigned int> indices;

    // Indices for a single triangle
    for (unsigned int i = 1; i <= 10; ++i) {
        indices.push_back(0); // Central vertex
        indices.push_back(i);
        indices.push_back(i % 10 + 1);
    }

    return indices;
}

std::vector<float> ShapeDefiner::GetCubeVertices(bool texCoordWanted)
{
    if (texCoordWanted)
    {
        return
        {
            // Front face
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,  // Position, Normal, TexCoord
             0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,

            // Back face
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
             0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,

            // Left face
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,

            // Right face
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,

             // Top face
             -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
              0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
              0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
             -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,

             // Bottom face
             -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
              0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
              0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
             -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f
        };
    }
    else {
        // Without texture coordinates
        return {
            // Front face
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  // Position, Normal
             0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

            // Back face
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
             0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

            // Left face
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,

            // Right face
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
             0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,

             // Top face
             -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
              0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
              0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
             -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,

             // Bottom face
             -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
              0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
              0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
             -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f
        };
    }
}


std::vector<unsigned int> ShapeDefiner::GetCubeIndices()
{
    return
    {
        // Front face
        0, 1, 2,
        2, 3, 0,

        // Back face
        4, 5, 6,
        6, 7, 4,

        // Left face
        8, 9, 10,
        10, 11, 8,

        // Right face
        12, 13, 14,
        14, 15, 12,

        // Top face
        16, 17, 18,
        18, 19, 16,

        // Bottom face
        20, 21, 22,
        22, 23, 20,
    };
}


std::vector<float> ShapeDefiner::GetPyramidVertices(bool texCoordWanted) {
    if (texCoordWanted) {
        return {
            // Base vertices (counter-clockwise order)
            -0.5f, 0.0f,  0.5f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,  // Vertex 0
             0.5f, 0.0f,  0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,  // Vertex 1
             0.5f, 0.0f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f,  // Vertex 2
            -0.5f, 0.0f, -0.5f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,  // Vertex 3

            // Apex vertex
             0.0f, 0.8f,  0.0f,   0.0f, 1.0f, 0.0f,   0.5f, 0.5f   // Vertex 4
        };
    }
    else {
        return {
            // Base vertices (counter-clockwise order)
             0.5f, -0.5f,  0.5f,   0.0f, -1.0f, 0.0f,  // Vertex 0
            -0.5f, -0.5f,  0.5f,   0.0f, -1.0f, 0.0f,  // Vertex 1
            -0.5f, -0.5f, -0.5f,   0.0f, -1.0f, 0.0f,  // Vertex 2
             0.5f, -0.5f, -0.5f,   0.0f, -1.0f, 0.0f,  // Vertex 3

             // Apex vertex
              0.0f,  0.8f,  0.0f,   0.0f,  1.0f, 0.0f   // Vertex 4
        };
    }
}
std::vector<unsigned int> ShapeDefiner::GetPyramidIndices()
{
    return
    {

        0, 1, 2,
        2, 3, 0,

        0, 4, 1,
        1, 4, 2,
        2, 4, 3,
        3, 4, 0
    };
}
std::vector<float> ShapeDefiner::GetPlaneVertices(bool texCoordWanted) {
    if (texCoordWanted) {
        return
        {
            // Positions            // Normals           // Texture coordinates
             0.5f,  0.0f,  0.5f,     0.0f,  1.0f,  0.0f,   1.0f, 1.0f,
             0.5f,  0.0f, -0.5f,     0.0f,  1.0f,  0.0f,   1.0f, 0.0f,
            -0.5f,  0.0f, -0.5f,     0.0f,  1.0f,  0.0f,   0.0f, 0.0f,
            -0.5f,  0.0f,  0.5f,     0.0f,  1.0f,  0.0f,   0.0f, 1.0f,
        };
    }
    else {
        return
        {
            // Positions            // Normals
             0.5f,  0.0f,  0.5f,     0.0f,  1.0f,  0.0f,
             0.5f,  0.0f, -0.5f,     0.0f,  1.0f,  0.0f,
            -0.5f,  0.0f, -0.5f,     0.0f,  1.0f,  0.0f,
            -0.5f,  0.0f,  0.5f,     0.0f,  1.0f,  0.0f,
        };
    }
}

std::vector<unsigned int> ShapeDefiner::GetPlaneIndices()
{
    return {
        0, 1, 2,
        2, 3, 0
    };
}

std::vector<float> ShapeDefiner::GetSphereVertices(bool texCoordWanted) {
    constexpr float pi = glm::pi<float>();
    constexpr float thetaDelta = pi / 50.0f;  // Controls vertical resolution
    constexpr float phiDelta = 2.0f * pi / 100.0f;  // Controls horizontal resolution

    std::vector<float> vertices;

    for (float theta = 0.0f; theta <= pi; theta += thetaDelta) {
        for (float phi = 0.0f; phi < 2.0f * pi; phi += phiDelta) {
            float x = std::sin(theta) * std::cos(phi);
            float y = std::cos(theta);
            float z = std::sin(theta) * std::sin(phi);

            // Normalize vertex position (not needed if already normalized)
            // float length = std::sqrt(x * x + y * y + z * z);
            // x /= length;
            // y /= length;
            // z /= length;

            // Position
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);

            // Normal (same as position for a sphere)
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);

            if (texCoordWanted) {
                // Texture coordinates
                float s = phi / (2.0f * pi);
                float t = theta / pi;
                vertices.push_back(s);
                vertices.push_back(t);
            }
        }
    }

    return vertices;
}

std::vector<unsigned int> ShapeDefiner::GetSphereIndices()
{
    std::vector<unsigned int> indices;

    constexpr int numTheta = 50;  // Number of horizontal slices
    constexpr int numPhi = 100;    // Number of vertical slices

    for (int i = 0; i < numTheta; ++i) {
        for (int j = 0; j < numPhi; ++j) {
            int first = i * (numPhi + 1) + j;
            int second = first + numPhi + 1;

            indices.push_back(first);
            indices.push_back(second);
            indices.push_back(first + 1);

            indices.push_back(second);
            indices.push_back(second + 1);
            indices.push_back(first + 1);
        }
    }

    return indices;
}


