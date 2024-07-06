#include "Matrix.h"
// Constructor that initializes a 4x4 matrix to identity
Matrix4::Matrix4()
{
    for (int i = 0; i < 16; ++i)
        data[i] = 0.0f;
    data[0] = data[5] = data[10] = data[15] = 1.0f;
}

// Constructor that initializes a 4x4 matrix to a diagonal matrix
Matrix4::Matrix4(float diagonal)
{
    for (int i = 0; i < 16; ++i)
        data[i] = 0.0f;
    data[0] = data[5] = data[10] = data[15] = diagonal;
}

// Returns an identity matrix
Matrix4 Matrix4::identity()
{
    return Matrix4(1.0f);
}

// Returns a translation matrix
Matrix4 Matrix4::translation(float x, float y, float z)
{
    Matrix4 result(1.0f);
    result.data[12] = x;
    result.data[13] = y;
    result.data[14] = z;
    return result;
}
Matrix4 Matrix4::rotationX(float angle)
{
    Matrix4 result(1.0f);
    float r = angle * M_PI / 180.0f; // Convert to radians
    result.data[0] = cos(r);
    result.data[1] = sin(r);
    result.data[4] = -sin(r);
    result.data[5] = cos(r);
    return result;
}
// Returns a rotation matrix around the Z axis
Matrix4 Matrix4::rotationZ(float angle)
{
    Matrix4 result(1.0f);
    float r = angle * M_PI / 180.0f; // Convert to radians
    result.data[0] = cos(r);
    result.data[1] = sin(r);
    result.data[4] = -sin(r);
    result.data[5] = cos(r);
    return result;
}
Matrix4 Matrix4::rotationY(float angle)
{
    Matrix4 result(1.0f);
    float r = angle * M_PI / 180.0f; // Convert to radians
    result.data[0] = cos(r);
    result.data[1] = sin(r);
    result.data[4] = -sin(r);
    result.data[5] = cos(r);
    return result;
}

// Returns a scaling matrix
Matrix4 Matrix4::scale(float x, float y, float z)
{
    Matrix4 result(1.0f);
    result.data[0] = x;
    result.data[5] = y;
    result.data[10] = z;
    return result;
}

// Multiplies two matrices
Matrix4 Matrix4::operator*(const Matrix4& other)
{
    Matrix4 result;
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            result.data[row * 4 + col] =
                data[row * 4 + 0] * other.data[0 * 4 + col] +
                data[row * 4 + 1] * other.data[1 * 4 + col] +
                data[row * 4 + 2] * other.data[2 * 4 + col] +
                data[row * 4 + 3] * other.data[3 * 4 + col];
        }
    }
    return result;
}

// Returns the pointer to the matrix data (used for setting uniform matrices in shaders)
float* Matrix4::getPointer()
{
    return data;
}
