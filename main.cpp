#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb/stb_image.h>

#include "Window.h"
#include "Camera.h"
#include "TriangleShader.h"
#include "ShapeDefiner.h"
#include "ShapeGenerator.h"
#include "Texture.h"
#include "CubeTexture.h"  // Ensure this is included

int windowWidth = 1600;
int windowHeight = 1080;

int main()
{
    Window window(windowWidth, windowHeight, "3rd Time Charm");
    Camera camera(glm::vec3(0.0f, 1.0f, 10.0f), windowWidth, windowHeight);
    TriangleShader shader("triangle.vert", "triangle.frag");
    TriangleShader cubeShader("cubemap.vert", "cubemap.frag");
    TriangleShader skyboxShader("skybox.vert", "skybox.frag");


    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL); // Set depth function to less than or equal to

    ShapeDefiner shapeDefiner;
    std::vector<float> sphereVertices = shapeDefiner.GetSphereVertices(false); // Can't be true. For later use as light source.
    std::vector<unsigned int> sphereIndices = shapeDefiner.GetSphereIndices();

    ShapeGenerator moonLight;
    moonLight.SetShape(sphereVertices, sphereIndices, false); // Set true for texture
    moonLight.Transformation(glm::vec3(-100.0f, 150.0f, -400.0f), 0.0f, glm::vec3(1.0f), glm::vec3(15.0f)); // Unity who?
    moonLight.SetColor(glm::vec3(0.9f, 0.9f, 0.9f));
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::vector<float> pyramidVertices = shapeDefiner.GetPyramidVertices(true); // For texture, set true.
    std::vector<unsigned int> pyramidIndices = shapeDefiner.GetPyramidIndices();
    ShapeGenerator pyramid;
    pyramid.SetShape(pyramidVertices, pyramidIndices, true); // Set true for texture
    pyramid.Transformation(glm::vec3(0.0f, 0.0f, -5.0f), 1.0f, glm::vec3(1.0f), glm::vec3(5.0f)); // Unity who?
    pyramid.SetColor(glm::vec3(0.1f, 0.5f, 0.3f));
    Texture pyramidTexture("nightSnow.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE); // Wise choice.
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::vector<float> oldCubeVertices = shapeDefiner.GetCubeVertices(false); // For texture, set true.
    std::vector<unsigned int> oldCubeIndices = shapeDefiner.GetCubeIndices();
    ShapeGenerator oldCube;
    oldCube.SetShape(oldCubeVertices, oldCubeIndices, false);
    oldCube.Transformation(glm::vec3(1.0f, 5.0f, 0.0f), 1.0f, glm::vec3(1.0f), glm::vec3(1.0f));
    oldCube.SetColor(glm::vec3(0.3f, 0.02f, 0.05f));
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::vector<float> planeVertices = shapeDefiner.GetPlaneVertices(true); // For texture, set true.
    std::vector<unsigned int> planeIndices = shapeDefiner.GetPlaneIndices();
    ShapeGenerator plane;
    plane.SetShape(planeVertices, planeIndices, true);
    plane.Transformation(glm::vec3(1.0f, -10.0f, 1.0f), 1.0f, glm::vec3(1.0f), glm::vec3(1000.0f));
    plane.SetColor(glm::vec3(0.3f, 0.02f, 0.05f));
    Texture planeTexture("frozenSnow.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE); 
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::vector<float> cubeVertices = shapeDefiner.GetCubeVertices(true); // For texture, set true.
    std::vector<unsigned int> cubeIndices = shapeDefiner.GetCubeIndices();
    ShapeGenerator cube;
    cube.SetCubeShape(cubeVertices, cubeIndices);  // Set up the cube shape

    // Load cubemap textures
    std::vector<std::string> faces = 
    {
        "right.jpg",
        "left.jpg",
        "top.jpg",
        "bottom.jpg",
        "front.jpg",
        "back.jpg"
    };
    CubeTexture cubeMap(faces);

    window.SetWindowColor(0.01f, 0.01f, 0.8f, 1.0f);
    window.SetRenderFunction([&]()
    {   
        std::cout << "Main loop running" << std::endl;
        camera.Inputs(window.GetGLFWWindow());

        // Calculate view and projection matrices
        glm::mat4 viewMatrix = camera.GetViewMatrix();
        glm::mat4 projectionMatrix = camera.GetProjectionMatrix(windowWidth / (float)windowHeight);

        // Render skybox first
        glDepthMask(GL_FALSE);  // Disable depth writing
        skyboxShader.Activate();
        skyboxShader.SetMat4("view", viewMatrix);
        skyboxShader.SetMat4("projection", projectionMatrix);
        cubeMap.Bind();

        glBindVertexArray(cube.ShapeVAO);
        glDrawElements(GL_TRIANGLES, cubeIndices.size(), GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);

        cubeMap.Unbind();
        glDepthMask(GL_TRUE);  // Enable depth writing again

        // Render other objects in the scene
        shader.Activate();  // Activate shader for other objects
        shader.SetMat4("view", viewMatrix);
        shader.SetMat4("projection", projectionMatrix);

        moonLight.Draw(viewMatrix, projectionMatrix, shader, nullptr);
        pyramid.Draw(viewMatrix, projectionMatrix, shader, &pyramidTexture);
        oldCube.Draw(viewMatrix, projectionMatrix, shader, nullptr);
        plane.Draw(viewMatrix, projectionMatrix, shader, &planeTexture);
    });

    // Run the main loop
    window.Run();
    window.~Window();
    return 0;
}
