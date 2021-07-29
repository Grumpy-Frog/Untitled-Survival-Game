#include "Player.h"


// public gets and sets functions
glm::vec3 Player::getPosition() const
{
	return this->playerPosition;
}

void Player::setPosition(glm::vec3& newPos)
{
	this->playerPosition = newPos;
}

float Player::getRadious() const
{
	return this->playerRadious;
}

void Player::setRadious(float& newRadious)
{
	this->playerRadious = newRadious;
}


// public funtions
Player::Player(const char* vertexShader, const char* fragmentShader, string model)
{
	this->playerPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	this->playerRadious = 0.0005f;
	this->playerShader = new Shader(vertexShader, fragmentShader);
	this->playerModel = new Model("Models/cube/cube.obj");
}

Player::~Player()
{
	cout << "Player destroyed\n";
	delete this->playerShader;
	delete this->playerModel;
}

void Player::Render(glm::mat4& projection, glm::mat4& view, Camera& camera)
{
	this->playerShader->use();
	this->playerShader->setMat4("projection", projection);
	this->playerShader->setMat4("view", view);

	/// draw player
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, playerPosition);
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	this->playerShader->setMat4("model", model);
	this->playerModel->Draw(*playerShader);
}