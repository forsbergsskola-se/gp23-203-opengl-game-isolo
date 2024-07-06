#include "ShapeDefiner.h"
#include <vector>
#include <cmath>
#include <glm/ext/scalar_constants.hpp>
# define M_PI           3.14159265358979323846



std::vector<float> ShapeDefiner::GetTriangleVertices(bool texCoordWanted)
{
    return 
    {

        -0.5f, 0.0f, -0.5f,   
         0.5f, 0.0f, -0.5f,  
         0.0f, 0.0f,  0.5f,  

         0.0f,  1.0f,  0.0f   
    };
}

std::vector<unsigned int> ShapeDefiner::GetTriangleIndices() 
{
    return {
        0, 1, 2, 

        0, 1, 3, 
        1, 2, 3,  
        2, 0, 3 
    };
}

std::vector<float> ShapeDefiner::GetCubeVertices(bool texCoordWanted) 
{
    return {
        
        // Front face
        -0.5f, -0.5f,  0.5f,   
         0.5f, -0.5f,  0.5f,  
         0.5f,  0.5f,  0.5f,  
        -0.5f,  0.5f,  0.5f,   

        // Back face
        -0.5f, -0.5f, -0.5f,  
         0.5f, -0.5f, -0.5f,   
         0.5f,  0.5f, -0.5f, 
        -0.5f,  0.5f, -0.5f, 

    };
}

std::vector<unsigned int> ShapeDefiner::GetCubeIndices() {
    return {
        // Front face
    0, 1, 2,
    2, 3, 0,

    // Back face
    4, 5, 6,
    6, 7, 4,

    // Left face
    4, 0, 3,
    3, 7, 4,

    // Right face
    1, 5, 6,
    6, 2, 1,

    // Top face
    3, 2, 6,
    6, 7, 3,

    // Bottom face
    4, 5, 1,
    1, 0, 4
    };
}

std::vector<float> ShapeDefiner::GetPyramidVertices(bool texCoordWanted)
{
    if (texCoordWanted)
    {
        return {


            -0.5f, 0.0f,  0.5f,     0.0f, 0.0f,
             0.5f, 0.0f,  0.5f,     1.0f, 0.0f,
             0.5f, 0.0f, -0.5f,     1.0f, 1.0f,
            -0.5f, 0.0f, -0.5f,     0.0f, 1.0f,

             0.0f, 0.8f,  0.0f,     0.5f, 0.5f
        };
    }
    else
    {
        return
        {
            0.5f, -0.5f,  0.5f,
           -0.5f, -0.5f,  0.5f,
           -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,

            0.0f,  0.5f,  0.0f
        };
    }
}
std::vector<unsigned int> ShapeDefiner::GetPyramidIndices()
{
    return {
       
        0, 1, 2,
        2, 3, 0,
       
        0, 4, 1,
        1, 4, 2,
        2, 4, 3,
        3, 4, 0
    };
}
std::vector<float> ShapeDefiner::GetPlaneVertices(bool texCoordWanted) 
{
    if (texCoordWanted) 
    {
        return {
           
             0.5f,  0.0f,  0.5f,  1.0f, 1.0f,
             0.5f,  0.0f, -0.5f,  1.0f, 0.0f,
            -0.5f,  0.0f, -0.5f,  0.0f, 0.0f,
            -0.5f,  0.0f,  0.5f,  0.0f, 1.0f,
        };
    }
    else {
        return {
            
             0.5f,  0.0f,  0.5f,
             0.5f,  0.0f, -0.5f,
            -0.5f,  0.0f, -0.5f,
            -0.5f,  0.0f,  0.5f,
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
    constexpr  float pi = glm::pi<float>();
    constexpr  float thetaDelta = pi / 10.0f;  // Controls vertical resolution
    constexpr  float phiDelta = 2.0f * pi / 20.0f;  // Controls horizontal resolution

    std::vector<float> vertices;

    for (float theta = 0.0f; theta <= pi; theta += thetaDelta) {
        for (float phi = 0.0f; phi < 2.0f * pi; phi += phiDelta) {
            float x = std::sin(theta) * std::cos(phi);
            float y = std::cos(theta);
            float z = std::sin(theta) * std::sin(phi);

            // Normalize vertex position (scale to unit length)
            float length = sqrt(x * x + y * y + z * z);
            x /= length;
            y /= length;
            z /= length;

            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);

            if (texCoordWanted) {
                // Calculate texture coordinates if needed
                float s = phi / (2.0f * pi);
                float t = theta / pi;
                vertices.push_back(s);
                vertices.push_back(t);
            }
        }
    }

    return vertices;
}
std::vector<unsigned int> ShapeDefiner::GetSphereIndices() {
    std::vector<unsigned int> indices;

    constexpr  int numTheta = 10;   // Number of horizontal slices
    constexpr  int numPhi = 20;     // Number of vertical slices

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


