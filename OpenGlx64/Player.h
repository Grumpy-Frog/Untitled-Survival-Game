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

	Shader* playerShader;
	Model* playerModel;

public:
	glm::vec3 getPosition() const;

	void setPosition(glm::vec3& newPos);

	float getRadious() const;

	void setRadious(float& newRadious);

public:
	Player(const char* vertexShader, const char* fragmentShader, string model);

	~Player();

	void Render(glm::mat4& projection, glm::mat4& view, Camera& camera);
};

#endif //PLAYER_H
