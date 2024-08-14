#pragma once
#include "Window.h"
#include "Camera.h"
#include <glm/fwd.hpp>
#include "Texture.h"
#include "CubeTexture.h"
class Create3Dobject
{
public:

	Create3Dobject();

	void CreateCube(Window& window, Camera& camera, const glm::vec4& colors, const glm::vec3& positions, const glm::vec3& scale, Texture* texture = nullptr);

	void CreateTriangle(Window& window, Camera& camera, const glm::vec4& colors, const glm::vec3& positions, const glm::vec3& scale, Texture* texture = nullptr);

	void CreatePyramid(Window& window, Camera& camera, const glm::vec4& colors, const glm::vec3& positions, const glm::vec3& scale, Texture* texture = nullptr);

	void CreatePlane(Window& window, Camera& camera, const glm::vec4& colors, const glm::vec3& positions, const glm::vec3& scale, Texture* texture = nullptr);

	void CreateSphere(Window& window, Camera& camera, const glm::vec4& colors, const glm::vec3& positions, const glm::vec3& scale, Texture* texture = nullptr);


private:

	Window& window;
	Camera& camera;

};
