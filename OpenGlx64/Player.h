#ifndef PLAYER_H
#define PLAYER_H

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>

#include <string>
#include <vector>

#include "Shader.h"
#include "model.h"
#include "Mesh.h"
#include "Camera.h"
using namespace std;


class Player
{
private:
	glm::vec3 playerPosition;
	float playerRadious;

public:
	glm::vec3 getPosition() const
	{
		return this->playerPosition;
	}

	void setPosition(glm::vec3& newPos)
	{
		this->playerPosition = newPos;
	}

	float getRadious()
	{
		return this->playerRadious;
	}
public:
	Player()
	{
		this->playerPosition = glm::vec3(2.0f, 0.0f, 2.0f);
		this->playerRadious = 0.0005f;
	}
	void init()
	{
		
	}

	void Update(glm::mat4 &projection, glm::mat4 &view, Shader &playerShader, Model &playerModel,Camera &camera)
	{
		
		playerShader.use();
		playerShader.setMat4("projection", projection);
		playerShader.setMat4("view", view);


		/// draw player
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, playerPosition);
		model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
		playerShader.setMat4("model", model);
		playerModel.Draw(playerShader);
	}

	void updateMovement(GLFWwindow* window, float deltaTime)
	{
		bool keyPressed = false;
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			this->playerPosition += glm::vec3(0.0f, 0.0f, 1.0f)*deltaTime;
			keyPressed = true;
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			this->playerPosition += glm::vec3(0.0f, 0.0f, -1.0f) * deltaTime;
			keyPressed = true;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			this->playerPosition += glm::vec3(1.0f, 0.0f, 0.0f) * deltaTime;
			keyPressed = true;
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			this->playerPosition += glm::vec3(-1.0f, 0.0f, 0.0f) * deltaTime;
			keyPressed = true;
		}
		if (!keyPressed)
		{
			//this->particle.setAcceleration(0.0f, 0.0f, 0.0f);
		}
	}
};

#endif //PLAYER_H
