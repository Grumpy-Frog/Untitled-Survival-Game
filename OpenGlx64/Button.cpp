#include "Button.h"

void Button::Update(glm::mat4& projection, glm::mat4& view, Camera& camera, float degree,float &deltaTime,
	glm::vec3 newScale, glm::vec3* pointLights)
{
	this->UpdateLighting(projection, view, camera, *this->myShader,deltaTime, pointLights);
	this->Render(projection, view, camera, newScale, degree);
}


void Button::Render(glm::mat4& projection, glm::mat4& view, Camera& camera, glm::vec3 newScale, float degree)
{
	/// draw player
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	model = glm::scale(model, newScale);
	model = glm::rotate(model, glm::radians(degree), glm::vec3(0.0f, 1.0f, 0.0f));
	this->myShader->setMat4("model", model);
	this->myModel->Draw(*this->myShader);
}

void Button::processInput(GLFWwindow* window, float& deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		glm::vec3 pos = this->getPosition();
		pos.x += velocity;
		this->setPosition(pos);
		//printPos();
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		glm::vec3 pos = this->getPosition();
		pos.x -= velocity;
		this->setPosition(pos);
		//printPos();
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		glm::vec3 pos = this->getPosition();
		pos.z -= velocity;
		this->setPosition(pos);
		//printPos();
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		glm::vec3 pos = this->getPosition();
		pos.z += velocity;
		this->setPosition(pos);
		//printPos();
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		this->velocity = 0.03f;
	}
	else
	{
		this->velocity = 0.01f;
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && this->position.y <= 0.0f)
	{
		this->jumpVelocity = 5.0f;
		this->isJumping = true;
	}

	if (this->isJumping)
	{
		calculateJump(deltaTime);
	}
	else if (this->isFalling)
	{
		this->jumpVelocity += gravity * deltaTime;
		this->position.y -= this->jumpVelocity * deltaTime;
	}

	if (this->position.y < 0.0f)
	{
		this->position.y = 0.0f;
		this->isJumping = false;
		this->isFalling = false;
	}

	if (this->position.x < -3.0f)
	{
		this->position.x = -3.0f;
	}
	if (this->position.x > 7.0f)
	{
		this->position.x = 7.0f;
	}
	if (this->position.z < 2.6f)
	{
		this->position.z = 2.6f;
	}
	if (this->position.z > 7.8f)
	{
		this->position.z = 7.8f;
	}
	//cout << this->position.x << " " << this->position.z << "\n";
}

void Button::calculateJump(float& deltaTime)
{
	this->jumpVelocity -= gravity * deltaTime;
	this->position.y += this->jumpVelocity * deltaTime;

	if (this->position.y >= 4.0f)
	{
		this->jumpVelocity = 0.0f;
		this->isJumping = false;
		this->isFalling = true;
	}
}