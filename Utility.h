#pragma once
#ifndef UTILITY_H
#define UTILITY_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shaderClass.h" 
#include <GLFW/glfw3.h>

class Utility
{
public:
    static void applyRotation(glm::quat& rotation, float angleSpeed)
    {
        float currentTime = static_cast<float>(glfwGetTime());
        float angle = currentTime * angleSpeed;
        glm::quat rotationDelta = glm::angleAxis(glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
        rotation = rotationDelta * rotation;
    }

    static void updateModelMatrix(glm::mat4& modelMatrix, glm::vec3 translation, glm::quat rotation, glm::vec3 scale)
    {
        modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, translation);
        modelMatrix = modelMatrix * glm::mat4_cast(rotation);
        modelMatrix = glm::scale(modelMatrix, scale);
    }

    static void setUniformMatrix(Shader& shader, const std::string& name, glm::mat4 matrix)
    {
        shader.Activate();
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    static void setUniformVector3(Shader& shader, const std::string& name, glm::vec3 vector)
    {
        shader.Activate();
        glUniform3fv(glGetUniformLocation(shader.ID, name.c_str()), 1, glm::value_ptr(vector));
    }
};

#endif // UTILITY_H
