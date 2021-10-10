#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "MazeGenerator.h"
using namespace std;

class Player : public Entity
{
private:
	int* myMaze;
	int* tempMaze;
	bool isJumping = false;

private:
	int prev_i = 1;
	int prev_j = 1;

	float speed;

public:
	void setJumpStatus(bool s)
	{
		this->isJumping = s;
	}

	bool getJumpStatus()
	{
		return this->isJumping;
	}

public:
	Player(const char* vertexShader, const char* fragmentShader, string model, int* maze, float speed = 10.0f);

	~Player();

	void Update()
	{
		
	}

	void printPos()
	{
		cout
			<< int(glm::round(this->getPosition().x)) / 2 << " "
			<< int(glm::round(this->getPosition().z)) / 2 << "\n";
	}

	glm::vec2 change_maze_according_to_player_pos()
	{
		int i = int(glm::round(this->getPosition().z)) / 2;
		int j = int(glm::round(this->getPosition().x)) / 2;

		if (i != prev_i || j != prev_j)
		{
			myMaze[prev_i * COL + prev_j] = tempMaze[prev_i * COL + prev_j];
		}

		if ((i != 0 && i != COL - 1) && (j != 0 && j != COL - 1))
		{
			prev_i = i;
			prev_j = j;
			//myMaze[i * COL + j] = 5;
		}

		return glm::vec2(prev_i, prev_j);
	}

	void processInput(GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			glm::vec3 pos = this->getPosition();
			pos.x += 0.01f;
			this->setPosition(pos);
			//printPos();
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			glm::vec3 pos = this->getPosition();
			pos.x -= 0.01f;
			this->setPosition(pos);
			//printPos();
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			glm::vec3 pos = this->getPosition();
			pos.z -= 0.01f;
			this->setPosition(pos);
			//printPos();
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			glm::vec3 pos = this->getPosition();
			pos.z += 0.01f;
			this->setPosition(pos);
			//printPos();
		}
	}

	void setSpeed(float newSpeed)
	{
		this->speed = newSpeed;
	}

	float getSpeed()
	{
		return this->speed;
	}
};

#endif //PLAYER_H
