#ifndef BUTTON_H
#define BUTTON_H

#include "Entity.h"
#include "Light.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>



class Button : public Entity, public Light
{
private:
	/// Extra///////
	float jumpVelocity = 0.0f;
	bool isJumping = false;
	bool isFalling = false;
	float gravity = 9.0f;
	float velocity = 0.01f;

public:
	Button(const char* vertexShader, const char* fragmentShader, string model)
		: Entity(vertexShader, fragmentShader, model)
	{
		//pass
	}

	~Button()
	{
		//this->dealloc();
		//entity already deallocated everything
	}

	void Update(glm::mat4& projection, glm::mat4& view, Camera& camera, float degree,
		glm::vec3 newScale, glm::vec3* pointLights);

	void Render(glm::mat4& projection, glm::mat4& view, Camera& camera, glm::vec3 newScale, float degree);


	//Extraaa//
public:
	void processInput(GLFWwindow* window, float& deltaTime);
	void calculateJump(float& deltaTime);
};
#endif // !BUTTON_H
