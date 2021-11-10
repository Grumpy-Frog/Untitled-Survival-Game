#pragma once
#include <iostream>
#include <algorithm>
#include <list>
#include <Windows.h>
#include <conio.h>

//#include "Entity.h"
#include "Player.h"
#include "MazeGenerator.h"
#include "Animation.h"
#include "Light.h"

#include "OpenAL/SoundDevice.h"
#include "OpenAL/SoundEffectsPlayer.h"
#include "OpenAL/SoundEffectsPlayer.h"

class Node
{
public:
	float g_score;
	float f_score;

	vector<Node*>neighbours;
	Node* parent = nullptr;
	bool isObstacle;
	bool isVisited;
	int x;
	int y;

	Node();
	~Node();
};


class A_Star_Path
{
public:
	Node* myNodes;
	Player* playerPtr;

	Node* startNode;
	Node* endNode;
	int* myMaze;


public:
	A_Star_Path(Player* player, int* maze);

	~A_Star_Path();

	void UpdateAllNodes();

	void UpdateNeighbours();

	void UpdatePlayerNode();

	void UpdateEnemyNode(glm::vec2& enemyIndex);

	void Update(glm::vec2& enemyPos);

	bool Solve_AStar();
};

class Enemy : public Entity, public Node, public Light
{
private:
	int* myMaze;
	int* tempMaze;
	Player* myPlayer_ptr;
	A_Star_Path* aStar;
	SoundEffectsPlayer* enemySoundPlayer;
	SoundEffectsPlayer* activationSoundPlayer;
	int enemyRoarAudio = 0;
	int activationSound = 0;

	int enemyID;

	//float ii = 0.0f;
	int prev_i;
	int prev_j;


private:
	glm::vec3 posDiff;
	float parentIndexX = -1.0f;
	float parentIndexZ = -1.0f;

	float velocity = 3.0f;
	float* deltaTime;
	float timePassed = 0.0f;
	Node* currentNode;
	bool aaa = 1;
	bool isActive = false;


	// Animation related stuffs
	Animation* myAnimation1;


	double getDistance(glm::vec3 p1, glm::vec3 p2);

	void calculatePlayer();

	void initRoarAudio(const char* s);

	void playSound();

	void StopSound();

public:
	Enemy(const char* vertexShader, const char* fragmentShader, vector<string>& model,
		glm::vec3 position, int id, float* dlTime,
		Player* player_ptr, int* maze,
		const char* enemyRoarAudio)
		: Entity(vertexShader, fragmentShader, model[0], glm::vec3(0.60f, 0.60f, 0.60f))
	{
		this->myPlayer_ptr = player_ptr;
		this->aStar = new A_Star_Path(player_ptr, maze);
		this->myMaze = maze;
		this->deltaTime = dlTime;
		this->setPosition(position);
		this->setMaze();
		this->setId(id);

		this->enemySoundPlayer = new SoundEffectsPlayer;
		this->initRoarAudio(enemyRoarAudio);
		this->activationSoundPlayer = new SoundEffectsPlayer;
		this->activationSound = SE_LOAD("Audio/enemyActive.ogg");

		this->myAnimation1 = new Animation(model);
		myAnimation1->setAnimModel();

	}

	~Enemy();

public:
	glm::vec2 getIndex();

	void deallocEnem();


	void Update(glm::mat4& projection, glm::mat4& view, Camera& camera,float &deltaTime, glm::vec3* pointLights);

public:
	void setId(int id);

	int getId() const;

	void setMaze();

	void setActive(bool active = true);

	bool getActive();

	Animation* getAnimation();
};

