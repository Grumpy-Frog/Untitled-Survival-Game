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

/*
class Car
{
public:
	rafi::Particle particle;

	Shader* carShader;
	Model* carModel;

	Car()
	{
		this->carShader = new Shader("modelVertex.shader", "modelFragment.shader");
		this->carModel = new Model("Models/cube/cube.obj");

		this->particle.setMass(7.0f);
		this->particle.setAcceleration(0.0f, 0.0f, 0.0f);
		this->particle.setDamping(0.9f);
		this->particle.setPosition(0.0f, 0.0f, 0.0f);

		this->particle.clearAccumulator();
	}

	void draw(glm::mat4 projection, glm::mat4 view)
	{

		this->carShader->use();
		this->carShader->setMat4("projection", projection);
		this->carShader->setMat4("view", view);


		rafi::Vector3 position;
		particle.getPosition(&position);

		// draw planet
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(position.x, position.y, position.z));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		this->carShader->setMat4("model", model);
		this->carModel->Draw(*carShader);
	}

	void update(GLFWwindow* window, float deltaTime)
	{
		bool keyPressed = false;
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			this->particle.setAcceleration(0.0f, -9.8f, 0.0f);
			keyPressed = true;
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			this->particle.setAcceleration(-2.0f, 0.0f, 0.0f);
			keyPressed = true;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			this->particle.setAcceleration(0.0f, 0.0f, 2.0f);
			keyPressed = true;
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			this->particle.setAcceleration(0.0f, 0.0f, -2.0f);
			keyPressed = true;
		}
		if (!keyPressed)
		{
			this->particle.setAcceleration(0.0f, 0.0f, 0.0f);
		}

		printf("%f %f %f\n",
			this->particle.getVelocity().x,
			this->particle.getVelocity().y,
			this->particle.getVelocity().z);
		this->particle.integrate(deltaTime);
	}
};
*/

class Player
{
private:
	glm::vec3 playerPosition;

public:
	glm::vec3 getPosition() const
	{
		return playerPosition;
	}
public:
	Player()
	{
		playerPosition = glm::vec3(2.0f, 0.0f, 2.0f);
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
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		playerShader.setMat4("model", model);
		playerModel.Draw(playerShader);
		
	}
};

#endif //PLAYER_H
