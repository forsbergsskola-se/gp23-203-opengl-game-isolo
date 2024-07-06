#ifndef SHAPEDEFINER_H
#define SHAPEDEFINER_H

#include <vector>
#include "ShapeGenerator.h"

class ShapeDefiner
{
    
public:


    std::vector<float> GetTriangleVertices(bool texCoordWanted);
    std::vector<unsigned int> GetTriangleIndices();

    std::vector<float> GetCubeVertices(bool texCoordWanted);
    std::vector<unsigned int> GetCubeIndices();


    std::vector<float> GetPyramidVertices(bool texCoordWanted);
    std::vector<unsigned int> GetPyramidIndices();

    std::vector<float> GetPlaneVertices(bool texCoordWanted);
    std::vector<unsigned int> GetPlaneIndices();

    std::vector<float> GetSphereVertices(bool texCoordWanted);
    std::vector<unsigned int> GetSphereIndices();


};
#endif // SHAPEDEFINER_H


