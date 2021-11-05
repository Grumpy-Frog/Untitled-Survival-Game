#include "Player.h"


// public funtions
Player::Player(const char* vertexShader, const char* fragmentShader, string model, int* maze,float speed)
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

	this->speed = speed;

	ALint attunation = AL_INVERSE_DISTANCE_CLAMPED;
	this->sd = SoundDevice::Get();
	this->sd->SetAttunation(attunation);

	this->soundPlayer = new SoundEffectsPlayer;
	this->soundPlayer->SetLooping(false);
	//this->walking = SE_LOAD("Audio/walking.ogg");
	this->running = SE_LOAD("Audio/running.ogg");
	this->jumping = SE_LOAD("Audio/jumping.ogg");
}
