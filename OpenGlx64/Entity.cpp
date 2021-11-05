#include "Entity.h"

Entity::Entity(const char* vertexShader, const char* fragmentShader, string model,
	glm::vec3 newScale)
{
	this->position = glm::vec3(2.0f, 0.0f, 2.0f);
	this->radious = 0.0006f;
	this->myShader = new Shader(vertexShader, fragmentShader);
	this->myModel = new Model(model);
	this->scale = newScale;
	this->angle = 90.0f;
}

Entity::Entity(Shader& shader, string modelS)
{
	this->myShader = myShader;
	this->myModel = new Model(modelS);
}

Entity::Entity()
{

}

Entity::~Entity()
{
	cout << "Entity destroyed\n";
	/*
	if (this->myShader)
	{
		delete this->myShader;
	}
	if (this->myModel)
	{
		delete this->myModel;
	}
	*/
}

void Entity::dealloc()
{
	if (this->myShader)
	{
		delete this->myShader;
	}
	if (this->myModel != NULL)
	{
		//delete this->myModel;
	}
}

void Entity::Render(glm::mat4& projection, glm::mat4& view, Camera& camera)
{
	this->myShader->use();
	this->myShader->setMat4("projection", projection);
	this->myShader->setMat4("view", view);



	/// draw player
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	model = glm::scale(model, this->scale);
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	this->myShader->setMat4("model", model);
	this->myModel->Draw(*myShader);
}


// public gets and sets functions
glm::vec3 Entity::getPosition() const
{
	return this->position;
}

void Entity::setPosition(glm::vec3& newPos)
{
	this->position = newPos;
}

float Entity::getRadious() const
{
	return this->radious;
}

void Entity::setRadious(float newRadious)
{
	this->radious = newRadious;
}

Model Entity::getModel() const
{
	return *this->myModel;
}

void Entity::setModel(Model* newModel)
{
	this->myModel = newModel;
}