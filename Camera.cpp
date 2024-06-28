#include "Camera.h"

// Constructor to initialize the camera with window dimensions and position
Camera::Camera(int width, int height, glm::vec3 position)
{
    // Initialize the width and height of the camera view
    Camera::width = width;
    Camera::height = height;
    // Set the initial position of the camera
    Position = position;
}

// Function to update the camera matrix
// This function takes the field of view (FOV) in degrees, the near clipping plane, and the far clipping plane as parameters
void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
    // Create view and projection matrices
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    // Set the view matrix based on the camera's position and orientation
    view = glm::lookAt(Position, Position + Orientation, Up);
    // Set the projection matrix based on the field of view, aspect ratio, near plane, and far plane
    projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);

    // Combine the projection and view matrices to form the camera matrix
    cameraMatrix = projection * view;
}

// Function to send the camera matrix to the shader
// This function takes a reference to the shader and the name of the uniform as parameters
void Camera::Matrix(Shader& shader, const char* uniform)
{
    // Upload the camera matrix to the specified uniform in the shader
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

// Function to process input from the keyboard and mouse to control the camera
// This function takes a pointer to the GLFW window as a parameter
void Camera::Inputs(GLFWwindow* window)
{
    // Move forward
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        Position += speed * Orientation;
    }
    // Move left
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        Position += speed * -glm::normalize(glm::cross(Orientation, Up));
    }
    // Move backward
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        Position += speed * -Orientation;
    }
    // Move right
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        Position += speed * glm::normalize(glm::cross(Orientation, Up));
    }
    // Move up
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        Position += speed * Up;
    }
    // Move down
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    {
        Position += speed * -Up;
    }
    // Increase movement speed
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        speed = 0.04f;
    }
    // Reset movement speed
    else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
    {
        speed = 0.010f;
    }

    // If the right mouse button is pressed, process mouse input for camera rotation
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
        // Hide the cursor
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        // Center the cursor on the first click
        if (firstClick)
        {
            glfwSetCursorPos(window, (width / 2), (height / 2));
            firstClick = false;
        }

        // Get the current mouse position
        double mouseX;
        double mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        // Calculate the rotation angles based on mouse movement
        float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
        float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

        // Rotate the camera orientation based on the calculated angles
        glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

        // Prevent the camera from flipping upside down
        if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
        {
            Orientation = newOrientation;
        }

        // Rotate the camera orientation around the up vector
        Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

        // Reset the cursor to the center of the screen
        glfwSetCursorPos(window, (width / 2), (height / 2));
    }
    // If the right mouse button is released, show the cursor and reset the first click flag
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        firstClick = true;
    }
}
