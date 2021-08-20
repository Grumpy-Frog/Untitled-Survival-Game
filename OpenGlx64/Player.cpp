#include "Player.h"


// public funtions
Player::Player(const char* vertexShader, const char* fragmentShader, string model, int* maze)
	: Entity(vertexShader, fragmentShader, model)
{
	this->myMaze = maze;
	tempMaze = new int[COL * COL];
	for (unsigned int i = 0; i < COL; i++)
	{
		for (unsigned int j = 0; j < COL; j++)
		{
			tempMaze[i * COL + j] = myMaze[i * COL + j];
		}
	}
}

Player::~Player()
{

}

