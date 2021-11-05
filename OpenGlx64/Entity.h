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
protected:
	glm::vec3 position;
	float radious;

	Shader* myShader;
	Model* myModel;
	string model;

	glm::vec3 scale;
	float angle;

public:
	Entity(const char* vertexShader, const char* fragmentShader, string model,
		glm::vec3 newScale = glm::vec3(1.0f, 1.0f, 1.0f));

	Entity(Shader& shader, string modelS);

	Entity();

	~Entity();

	virtual void dealloc();

	virtual void Render(glm::mat4& projection, glm::mat4& view, Camera& camera);


public:
	// public gets and sets functions
	glm::vec3 getPosition() const;

	void setPosition(glm::vec3& newPos);

	float getRadious() const;

	void setRadious(float newRadious);

	Model getModel() const;

	void setModel(Model* newModel);
};

