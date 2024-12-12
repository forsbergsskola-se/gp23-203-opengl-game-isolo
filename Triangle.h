#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include "Triangle.h"

class Triangle 
{
public:
    Triangle(const char* vertexPath, const char* fragmentPath);
    ~Triangle();
                


    GLuint CombinedVAO;
    TriangleShader* shader; 

    std::vector<float> vertices; 
    std::vector<unsigned int> indices;


    void setUp_3D_Triangle_Data();

    void setUp_Triangle_Position_Data();
    void setUp_Triangle_Rotation_Data();
    void setUp_Triangle_Scale_Data();

    void store_Data_To_Buffer();


};

#endif