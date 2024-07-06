#ifndef CAMERA_H
#define CAMERA_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

class Camera
{
public:
    Camera(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f), float width = 1600.0f, float height = 1080.0f);

    // Camera transformations
    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix(float aspectRatio) const;

    // Handles camera input
    void Inputs(GLFWwindow* window);

    // Debugging method to print camera details
private:
    // Camera attributes
    glm::vec3 Position;
    glm::vec3 Up;
    glm::vec3 Orientation;

    // Projection settings
    float FOV;

    // Input settings
    float speed;
    float sensitivity;
    bool firstClick;
    float width, height;

    static constexpr float DEFAULT_FOV = 45.0f;
};

#endif // CAMERA_H
