// have to add light class

#ifndef LIGHT_H
#define LIGHT_H

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "shader.h"
#include "Camera.h"

class Light
{
private:
	
	float ambient = 0.0f;;
	float counter = 0.01f;

public:
	Light();

	~Light();

	void UpdateLighting(glm::mat4& projection, glm::mat4& view, Camera& camera, Shader& myShader,
		glm::vec3* pointLightPositions);

	void updateAmbient();
};

#endif // !LIGHT_H
