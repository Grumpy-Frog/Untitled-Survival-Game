#ifndef LIGHTCUBE_H
#define LIGHTCUBE_H


#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "shader.h"
#include "Camera.h"

class LightCube
{
private:
	Shader* lightCubeShader;

	glm::vec3 scale;
	glm::vec3 position;
	float* vertices;
	unsigned int VBO, cubeVAO;
	unsigned int lightCubeVAO;

public:
	LightCube(const char* vertexShader, const char* fragmentShader,
		glm::vec3 pos, float* vert,
		glm::vec3 newScale = glm::vec3(1.0f, 1.0f, 1.0f));

	~LightCube();

	void initBuffer();

	void Render(glm::mat4& projection, glm::mat4& view, Camera& camera,
		float angle,
		glm::vec3 newScale = glm::vec3(1.0f, 1.0f, 1.0f));

	glm::vec3 getPosition() const;

	void setPosition(glm::vec3 newPos);

	glm::vec3 getScale() const;

	void setScale(glm::vec3 newScale);
};

#endif // !LIGHTCUBE_H
