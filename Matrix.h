#ifndef MATRIX_H
#define MATRIX_H
#ifndef M_PI
#define M_PI 3.14159265358979323846

#include <iostream>
#include <cmath>
#include <math.h>


class Matrix4 
{
public:
    float data[16];

    Matrix4();
    Matrix4(float diagonal);
    static Matrix4 identity();
    static Matrix4 translation(float x, float y, float z);

    static Matrix4 rotationX(float angle);
    static Matrix4 rotationZ(float angle);
    static Matrix4 rotationY(float angle);

    static Matrix4 scale(float x, float y, float z);
    Matrix4 operator*(const Matrix4& other);
    float* getPointer();
}; 
#endif
#endif


