#include "Headers.h"

int windowWidth = 1600;
int windowHeight = 1080;

int main() {
    Window window(windowWidth, windowHeight, "3rd Time Charm");
    window.SetWindowColor(1.0f, 0.0f, 0.74f, 1.0f);
    Camera camera(glm::vec3(1.0f, 2.0f, 10.0f), windowWidth, windowHeight);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL); // Set depth function to less than or equal to

    TriangleShader shader("triangle.vert", "triangle.frag");

    Texture planeTexture("nightSky1.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture cubeTexture("blackPaper.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

    ShapeDefiner shapeData;
    std::vector<float> skyboxVertices = shapeData.GetSphereVertices(false);
    std::vector<unsigned int> skyboxIndices = shapeData.GetSphereIndices();
    Skybox drawSkybox;
    drawSkybox.SetSkybox(skyboxVertices, skyboxIndices);

    std::vector<float> lightShapeVertices = shapeData.GetSphereVertices(false);
    std::vector<unsigned int> lightShapeIndices = shapeData.GetSphereIndices();

    Light light;
    light.LightShape(lightShapeVertices, lightShapeIndices);
    light.SetScale(glm::vec3(0.3f, 0.3f, 0.3f));


    glm::vec3 lightSourcePos = glm::vec3(3.0f, 2.0f, -3.5f); ///CombinedPosition, Light Color position + Light Source position.
    ShapeGenerator lightPos;
    lightPos.SetLightPos(glm::vec3(1.0f, 1.0f, -1.0f));
    glm::vec3 initialPosition = glm::vec3(0.0f, 1.0f, 0.0f);
    light.SetPositionAndColor(shader, glm::vec3(3.0f, 3.0f, -3.5f), glm::vec3(1.0f, 1.0f, 1.0f));


    Create3Dobject create;
    window.SetRenderFunction([&]()
        {
            camera.Inputs(window.GetGLFWWindow());
            camera.CameraON();
            // Draw Skybox First
            drawSkybox.DrawSkybox(window, camera);
            /////////////////////////////////////////////////
            create.CreatePlane(window, camera, glm::vec4(0.192f, 0.192, 0.192f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(50.0f), &planeTexture);

            create.CreateCube(window, camera, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec3(2.0f, 3.0f, -1.0f), glm::vec3(1.0f));
            create.CreatePyramid(window, camera, glm::vec4(0.192f, 1.0f, 0.192f, 1.0f), glm::vec3(0.0f, 1.0f, -1.0f), glm::vec3(1.0f));
            create.CreateSphere(window, camera, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec3(-2.0f, 1.0f, -1.0f), glm::vec3(0.5f));
            create.CreatePlane(window, camera, glm::vec4(0.192f, 0.0f, 0.192f, 1.0f), glm::vec3(4.0f, 1.0f, -1.0f), glm::vec3(1.0f));

            create.CreateTriangle(window, camera, glm::vec4(0.192f, 0.0f, 0.192f, 1.0f), glm::vec3(4.0f, 3.0f, -1.0f), glm::vec3(1.0f));
            create.CreateCube(window, camera, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(2.0f, 1.0f, -1.0f), glm::vec3(1.0f), &cubeTexture);

            light.LightOn(window, camera, true);

        });

    window.Run();
    return 0;
}
