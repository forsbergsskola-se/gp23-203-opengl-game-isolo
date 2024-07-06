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

int windowWidth = 1600;
int windowHeight = 1080;

unsigned int loadTexture(const char* path);
unsigned int loadCubemap(std::vector<std::string> faces);

int main()
{
    Window window(windowWidth, windowHeight, "3rd Time Charm");
    glEnable(GL_DEPTH_TEST);

    TriangleShader cubeShader("cubemap.vert", "cubemap.frag");

    std::cout << "cubeShader created successfully." << std::endl;

    TriangleShader skyboxShader("skybox.vert", "skybox.frag");
    std::cout << "skyboxShader created successfully." << std::endl;

    TriangleShader shader("triangle.vert", "triangle.frag");
    std::cout << "shader created successfully." << std::endl;

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    std::cout << "Setting up cube vertices..." << std::endl;

    float cubeVertices[] =
    {
        // positions          // texture Coords
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f

    };
    std::cout << "cubeVertices set up" << std::endl;
    std::cout << "Setting up skybox Vertices..." << std::endl;

    float skyboxVertices[] = {
        // positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };
    std::cout << "Skybox vertices ready." << std::endl;

    std::cout << "Setting up cube VAO..." << std::endl;
    // cube VAO
    unsigned int cubeVAO, cubeVBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    std::cout << "VAO setup ready." << std::endl;
    std::cout << "Setting up skybox VAO..." << std::endl;
    // skybox VAO
    unsigned int skyboxVAO, skyboxVBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    std::cout << "Skybox VAO ready." << std::endl;
    // load textures
    // -------------
    std::cout << "Loading texture container..." << std::endl;

    unsigned int cubeTexture = loadTexture("container.jpg");
    std::cout << "Loading faces..." << std::endl;

    std::vector<std::string> faces
    {
        "right.jpg",
        "left.jpg",
        "top.jpg",
        "bottom.jpg",
        "front.jpg",
        "back.jpg"
    };

    unsigned int cubemapTexture = loadCubemap(faces);

    // shader configuration
    // --------------------
    cubeShader.Activate();
    cubeShader.SetBool("texture1", 0);

    skyboxShader.Activate();
    skyboxShader.SetInt("skybox", 0);

    ShapeDefiner definer;
    ShapeGenerator genCube;

    ShapeDefiner shapeDefiner;
    std::vector<float> sphereVertices = shapeDefiner.GetSphereVertices(false); //Can't be true. For later use as light source.
    std::vector<unsigned int> sphereIndices = shapeDefiner.GetSphereIndices();

    ShapeGenerator moonLight;
    moonLight.SetShape(sphereVertices, sphereIndices, false); // Set true for texture
    moonLight.Transformation(glm::vec3(1.0f, 75.0f, -100.0f), 0.0f, glm::vec3(1.0f), glm::vec3(5.0f)); //Unity who?
    moonLight.SetColor(glm::vec3(0.9f, 9.0f, 0.9f));

    std::vector<float> flexibleVertices = shapeDefiner.GetCubeVertices(true); // For texture, set true.
    std::vector<unsigned int> flexibleIndices = shapeDefiner.GetCubeIndices();

    ShapeGenerator flexible;
    flexible.SetShape(flexibleVertices, flexibleIndices, true); // Set true for texture
    flexible.Transformation(glm::vec3(0.0f, 0.0f, -5.0f), 0.0f, glm::vec3(1.0f), glm::vec3(1.0f)); //Unity who?
    flexible.SetColor(glm::vec3(0.1f, 0.5f, 0.3f));



    Texture texture("steelBox.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE); //Wise choice.
    Camera camera(glm::vec3(0.0f, 1.0f, 10.0f), windowWidth, windowHeight);
    std::cout << "Camera created successfully" << std::endl;
    window.SetWindowColor(0.01f, 0.01f, 0.8f, 1.0f);
    window.SetRenderFunction([&]()
        {
            std::cout << "Main loop running" << std::endl;
            cubeShader.Activate();
            // Update camera view and projection matrices
            glm::mat4 viewMatrix = camera.GetViewMatrix();
            glm::mat4 projectionMatrix = camera.GetProjectionMatrix(windowWidth / windowHeight);
            camera.Inputs(window.GetGLFWWindow());

            moonLight.Draw(viewMatrix, projectionMatrix, shader, nullptr);
            flexible.Draw(viewMatrix, projectionMatrix, shader, &texture);

            // cubes
            std::cout << "Rendering Cube." << std::endl;

            glBindVertexArray(cubeVAO);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, cubeTexture);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            glBindVertexArray(0);

            // draw skybox as last
            std::cout << "Rendering skybox." << std::endl;

            glDepthFunc(GL_LEQUAL);
            skyboxShader.Activate();
            viewMatrix = glm::mat4(glm::mat3(camera.GetViewMatrix())); // remove translation from the view matrix
            skyboxShader.SetMat4("view", viewMatrix);
            skyboxShader.SetMat4("projection", projectionMatrix);
            // skybox cube
            std::cout << "Rendering skybox cube." << std::endl;

            glBindVertexArray(skyboxVAO);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            glBindVertexArray(0);
            glDepthFunc(GL_LESS); // set depth function back to default   
        });

    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &skyboxVAO);
    glDeleteBuffers(1, &cubeVBO);
    glDeleteBuffers(1, &skyboxVBO);

    // Run the main loop
    window.Run();
    window.~Window();
    return 0;
}
unsigned int loadTexture(const char* path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format{};
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        // Set texture parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
        std::cout << "Texture loaded " << path << std::endl;

    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
        textureID = 0; // Return 0 to indicate failure
    }

    return textureID;
}

// Creating a cubemap.
unsigned int loadCubemap(std::vector<std::string> textures_faces)
{
    std::cout << "Cubemap texture loading... " << std::endl;

    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    unsigned char* data;
    for (unsigned int i = 0; i < textures_faces.size(); i++)
    {
        data = stbi_load(textures_faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {

            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
            std::cout << "Cubemap texture loaded. " << std::endl;

        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << textures_faces[i] << std::endl;
            stbi_image_free(data);
            textureID = 0; // Return 0 to indicate failure
            break;
        }
    }

    // Set cubemap texture parameters
    if (textureID != 0)
    {
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        std::cout << "Returning Texture ID. " << std::endl;
    }
    return textureID;
}