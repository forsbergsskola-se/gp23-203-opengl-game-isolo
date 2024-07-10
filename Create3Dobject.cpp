#include "Create3DObject.h"
#include "ShapeDefiner.h"
#include "ShapeGenerator.h"
#include "Texture.h"
#include "SkyBox.h"


Create3Dobject::Create3Dobject(): window(window), camera(camera){}
void Create3Dobject::CreateCube(Window& window, Camera& camera, const glm::vec4& colors, const glm::vec3& positions,  const glm::vec3& scale, Texture* texture)
{	
	ShapeDefiner defineCube;
    ShapeGenerator genCube;

    std::vector<float> cubeVertices = defineCube.GetCubeVertices(true); // For texture, set true.
    std::vector<unsigned int> cubeIndices = defineCube.GetCubeIndices();
    genCube.SetShape(cubeVertices, cubeIndices, true); // Set true for texture
    genCube.Transformation(glm::vec3(positions), 1.0f, glm::vec3(1.0f), glm::vec3(scale)); // Unity who?
    genCube.SetShapeColor(glm::vec4(colors));

    
    if (texture !=nullptr)
    {
        genCube.Draw(window, camera, texture);
    }
    else
    {
        genCube.Draw(window, camera, nullptr);
    }
}
/*
void Create3Dobject::CreateLight(Window& window, Camera& camera, bool showSource)
{
    ShapeDefiner defineCubemap;
    Skybox skybox;
    defineCubemap.GetCubemapVertices();
    
} 
*/
void Create3Dobject::CreatePyramid(Window& window, Camera& camera, const glm::vec4& colors, const glm::vec3& positions, const glm::vec3& scale, Texture* texture)
{
    ShapeDefiner definePyramid;
    ShapeGenerator genPyramid;

    std::vector<float>pyramidVertices = definePyramid.GetPyramidVertices(true);
    std::vector<unsigned int> pyramidIndices = definePyramid.GetPyramidIndices();
    genPyramid.SetShape(pyramidVertices, pyramidIndices, true);
    genPyramid.Transformation(glm::vec3(positions), 1.0f, glm::vec3(1.0f), glm::vec3(scale)); // Unity who?
    genPyramid.SetShapeColor(glm::vec4(colors));

    if (texture != nullptr)
    {
        genPyramid.Draw(window, camera, texture);
    }
    else
    {
        genPyramid.Draw(window, camera, nullptr);
    }

}
void Create3Dobject::CreatePlane(Window& window, Camera& camera, const glm::vec4& colors, const glm::vec3& positions, const glm::vec3& scale, Texture* texture)
{
    ShapeDefiner defineplane;
    ShapeGenerator genPlane;

    std::vector<float>planeVertices = defineplane.GetPlaneVertices(true);
    std::vector<unsigned int> planeIndices = defineplane.GetPlaneIndices();
    genPlane.SetShape(planeVertices, planeIndices, true);
    genPlane.Transformation(glm::vec3(positions), 1.0f, glm::vec3(1.0f), glm::vec3(scale)); // Unity who?
    genPlane.SetShapeColor(glm::vec4(colors));

    if (texture != nullptr)
    {
        genPlane.Draw(window, camera, texture);
    }
    else
    {
        genPlane.Draw(window, camera, nullptr);
    }

}

void Create3Dobject::CreateSphere(Window& window, Camera& camera, const glm::vec4& colors, const glm::vec3& positions, const glm::vec3& scale, Texture* texture)
{
    ShapeDefiner defineSphere;
    ShapeGenerator genSphere;

    std::vector<float>pyramidVertices = defineSphere.GetSphereVertices(true);
    std::vector<unsigned int> pyramidIndices = defineSphere.GetSphereIndices();
    genSphere.SetShape(pyramidVertices, pyramidIndices, true);
    genSphere.Transformation(glm::vec3(positions), 1.0f, glm::vec3(1.0f), glm::vec3(scale)); // Unity who?
    genSphere.SetShapeColor(glm::vec4(colors));

    if (texture != nullptr)
    {
        genSphere.Draw(window, camera, texture);
    }
    else
    {
        genSphere.Draw(window, camera, nullptr);
    }

}


