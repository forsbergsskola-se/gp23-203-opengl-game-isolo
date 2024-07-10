#include "Headers.h"

int windowWidth = 1600;
int windowHeight = 1080;



int main()
{
    Window window(windowWidth, windowHeight, "3rd Time Charm");
    window.SetWindowColor(0.0f, 0.0f, 0.0f, 1.0f);
    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), windowWidth, windowHeight);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL); // Set depth function to less than or equal to

    Texture planeTexture("blackPaper.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    ShapeDefiner shapeData;
    std::vector<float> skyboxVertices = shapeData.GetCubemapVertices();
    std::vector<unsigned int> skyboxIndices = shapeData.GetCubemapIndices();
    Skybox drawSkybox;
    drawSkybox.SetSkybox(skyboxVertices, skyboxIndices);


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

    std::vector<float> lightShapeVertices = shapeData.GetSphereVertices(false);
    std::vector<unsigned int> lightShapeIndices = shapeData.GetSphereIndices();
    Light light;
    light.LightShape(lightShapeVertices, lightShapeIndices);
    light.SetPosition(glm::vec3(2.0f, 1.0f, -3.0f));
    light.SetScale(glm::vec3(0.2f, 0.2f, 0.2f));
    Create3Dobject create;
    window.SetRenderFunction([&]()
    {
        
       camera.Inputs(window.GetGLFWWindow());
       camera.CameraON();
       //DrawSkybox First
      //  drawSkybox.DrawSkybox(window, camera, cubeMap);
        /////////////////////////////////////////////////
             
       create.CreatePlane(window, camera, glm::vec4 (0.0f, 0.0f, 1.0f, 1.0f), glm::vec3 (0.0f, -1.0f, 0.0f), glm::vec3 (10.0f), &planeTexture);
       create.CreateCube(window, camera, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f));
       light.LightOn(window, camera, true);

    });

    window.Run();
    return 0;
}
