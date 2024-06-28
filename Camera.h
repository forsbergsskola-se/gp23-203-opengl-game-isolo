#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "shaderClass.h"

class Camera
{
public:
    // Camera position in 3D space
    glm::vec3 Position;
    // Camera orientation vector, points to where the camera is looking
    glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    // Up vector of the camera, used to keep the camera oriented correctly
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
    // Camera matrix used for transforming coordinates to view space
    glm::mat4 cameraMatrix = glm::mat4(1.0f);

    // Window width
    int width;
    // Window height
    int height;

    // Speed of the camera movement
    float speed = 0.1f;
    // Sensitivity of the camera rotation
    float sensitivity = 100.0f;

    // Flag to check if the mouse click is the first one
    bool firstClick = true;

    // Constructor to initialize the camera with window dimensions and position
    Camera(int width, int height, glm::vec3 position);

    // Updates the camera matrix based on the camera's position and orientation
    void updateMatrix(float FOVdeg, float nearPlane, float farPlane);

    // Sends the camera matrix to the shader
    void Matrix(Shader& shader, const char* uniform);

    // Processes input from the keyboard and mouse to control the camera
    void Inputs(GLFWwindow* window);
};

#endif
