#include "Light.h"

Light::Light()
	: lightSourceVAO(0), lightSourceEBO(0), lightSourceVBO(0), lightPos(glm::vec3(0.0f)),
	rotation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)), scale(glm::vec3(1.0f)), lightSourceColor(glm::vec3(1.0f)),
	lightSourceShader("lightSource.vert", "lightSource.frag"),
	window(window), camera(camera), lightShader(lightShader)
{
	// Constructor initializes member variables and loads shaders
}

Light::~Light() {
	// Destructor deletes OpenGL buffers
	glDeleteVertexArrays(1, &lightSourceVAO);
	glDeleteBuffers(1, &lightSourceVBO);
	glDeleteBuffers(1, &lightSourceEBO);
}
void Light::LightShape(const std::vector<float>& lightSourceVertices, const std::vector<unsigned int>& lightSourceIndices)
{
	this->lightSourceVertices = lightSourceVertices;
	this->lightSourceIndices = lightSourceIndices;

	// Generate and bind VAO
	glGenVertexArrays(1, &lightSourceVAO);
	glBindVertexArray(lightSourceVAO);
	CheckGLError("Generating and binding VAO in Light.cpp");

	// Generate and bind VBO, then set data
	glGenBuffers(1, &lightSourceVBO);
	glBindBuffer(GL_ARRAY_BUFFER, lightSourceVBO);
	glBufferData(GL_ARRAY_BUFFER, lightSourceVertices.size() * sizeof(float), lightSourceVertices.data(), GL_STATIC_DRAW);
	CheckGLError("Generating and binding VBO in Light.cpp");

	// Generate and bind EBO, then set data
	glGenBuffers(1, &lightSourceEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lightSourceEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, lightSourceIndices.size() * sizeof(unsigned int), lightSourceIndices.data(), GL_STATIC_DRAW);
	CheckGLError("Generating and binding EBO in Light.cpp");

	// Set position attribute pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	CheckGLError("Setting position attribute pointer in Light.cpp");
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Unbind the VAO to prevent accidental modification
	glBindVertexArray(0);
	CheckGLError("Unbinding VAO in Light.cpp");

	// Optionally unbind the VBO (not strictly necessary)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	CheckGLError("Unbinding VBO in Light.cpp");
}
void Light::LightOn(Window& window, Camera& camera, bool showLightSource)
{
	float aspectRatio = static_cast<float>(window.getWidth()) / static_cast<float>(window.getHeight());
	glm::mat4 view = camera.GetViewMatrix();
	glm::mat4 projection = camera.GetProjectionMatrix(aspectRatio);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, lightPos);
	model = glm::scale(model, scale);

	glm::mat4 MVP = projection * view * model;

	if (showLightSource)
	{
		std::cout << "Activating Light Source Shader.." << std::endl;
		lightSourceShader.Activate();

		glBindVertexArray(lightSourceVAO);
		CheckGLError("lightSourceShader vertex array binding");
		lightSourceShader.SetColor("lightSourceColor", lightSourceColor);
		lightSourceShader.SetMat4("lightMVP", MVP);
		CheckGLError("lightSourceShader MVP uniform");

		glDrawElements(GL_TRIANGLES, lightSourceIndices.size(), GL_UNSIGNED_INT, nullptr);
		CheckGLError("lightSourceShader draw elements");

		glBindVertexArray(0);
	}
}
void Light::SetPositionAndColor(TriangleShader& lightShader, const glm::vec3& lightPos, const glm::vec3& lightSourceColor)
{
	this->lightPos = lightPos;
	this->lightSourceColor = lightSourceColor;
}
void Light::SetScale(const glm::vec3& scale)
{
	this->scale = scale;
}
void Light::CheckGLError(const std::string& location) {
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		std::cerr << "OpenGL error in " << location << ": " << err << std::endl;
	}
}
