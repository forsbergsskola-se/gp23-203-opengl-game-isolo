#include "ShapeDefiner.h"
#include <vector>
#include <cmath>
#include <glm/ext/scalar_constants.hpp>
# define M_PI           3.14159265358979323846




std::vector<float> ShapeDefiner::GetCubemapVertices()
{
    return
    {
        // positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,

        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f
    };
}
std::vector<unsigned int> ShapeDefiner::GetCubemapIndices()
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
        22, 23, 20

    };
}

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
    if (texCoordWanted) 
    {

        return 
        {
            // Front face
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,

            // Back face
            -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
             0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,

            // Left face
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,

            // Right face
             0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,

             // Top face
             -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
              0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
              0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,

             // Bottom face
             -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
              0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
              0.5f, -0.5f,  0.5f,  1.0f, 1.0f,
             -0.5f, -0.5f,  0.5f,  0.0f, 1.0f,
        };
    }
    else {
        // Without texture coordinates
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

            // Left face
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f,

            // Right face
             0.5f, -0.5f, -0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
             0.5f,  0.5f, -0.5f,

             // Top face
             -0.5f,  0.5f,  0.5f,
              0.5f,  0.5f,  0.5f,
              0.5f,  0.5f, -0.5f,
             -0.5f,  0.5f, -0.5f,

             // Bottom face
             -0.5f, -0.5f, -0.5f,
              0.5f, -0.5f, -0.5f,
              0.5f, -0.5f,  0.5f,
             -0.5f, -0.5f,  0.5f,
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

std::vector<float> ShapeDefiner::GetSphereVertices(bool texCoordWanted) 
{
    constexpr float pi = glm::pi<float>();
    constexpr float thetaDelta = pi / 50.0f;  // Controls vertical resolution
    constexpr float phiDelta = 2.0f * pi / 100.0f;  // Controls horizontal resolution

    std::vector<float> vertices;

    for (float theta = 0.0f; theta <= pi; theta += thetaDelta) {
        for (float phi = 0.0f; phi < 2.0f * pi; phi += phiDelta) {
            float x = std::sin(theta) * std::cos(phi);
            float y = std::cos(theta);
            float z = std::sin(theta) * std::sin(phi);

            // Normalize vertex position
            float length = std::sqrt(x * x + y * y + z * z);
            x /= length;
            y /= length;
            z /= length;

            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);

            if (texCoordWanted) 
            {
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


