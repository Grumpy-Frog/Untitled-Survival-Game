#pragma once

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>

#include <string>
#include <vector>

#include "Shader.h"
#include "model.h"
#include "Mesh.h"
#include "Camera.h"

class Entity
{
private:
	glm::vec3 position;
	float radious;

	Shader* myShader;
	Model* myModel;

public:
	Entity(const char* vertexShader, const char* fragmentShader, string model)
	{
		this->position = glm::vec3(2.0f, 0.0f, 2.0f);
		this->radious = 0.0006f;
		this->myShader = new Shader(vertexShader, fragmentShader);
		this->myModel = new Model(model);
	}
	~Entity()
	{
		cout << "Entity destroyed\n";
		//delete this->myShader;
		//delete this->myModel;
	}

	void Render(glm::mat4& projection, glm::mat4& view, Camera& camera)
	{
		this->myShader->use();
		this->myShader->setMat4("projection", projection);
		this->myShader->setMat4("view", view);



		/// draw player
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, position);
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		this->myShader->setMat4("model", model);
		this->myModel->Draw(*myShader);
	}


public:
	// public gets and sets functions
	glm::vec3 getPosition() const
	{
		return this->position;
	}

	void setPosition(glm::vec3& newPos)
	{
		this->position = newPos;
	}

	float getRadious() const
	{
		return this->radious;
	}

	void setRadious(float& newRadious)
	{
		this->radious = newRadious;
	}
};

