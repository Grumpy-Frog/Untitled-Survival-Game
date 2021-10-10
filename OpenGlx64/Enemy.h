#pragma once
#include <iostream>
#include <algorithm>
#include <list>
#include <Windows.h>
#include <conio.h>

//#include "Entity.h"
#include "Player.h"
#include "MazeGenerator.h"



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

	Node()
	{
		this->g_score = INFINITY;
		this->f_score = INFINITY;
		this->neighbours.clear();
		this->parent = nullptr;
		this->isObstacle = false;
		this->isVisited = false;
		this->x = 0;
		this->y = 0;
	}
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
	A_Star_Path(Player* player, int* maze)
	{
		this->playerPtr = player;
		this->myMaze = maze;
		this->myNodes = new Node[COL * COL];
		UpdateAllNodes();
		UpdateNeighbours();
	}

	void UpdateAllNodes()
	{
		for (int x = 0; x < COL; x++)
		{
			for (int y = 0; y < COL; y++)
			{
				this->myNodes[x * COL + y].x = x;
				this->myNodes[x * COL + y].y = y;
				this->myNodes[x * COL + y].g_score = INFINITY;
				this->myNodes[x * COL + y].f_score = INFINITY;
				this->myNodes[x * COL + y].parent = nullptr;
				this->myNodes[y * COL + x].neighbours.clear();
				if (this->myMaze[x * COL + y] == 1)
				{
					this->myNodes[x * COL + y].isObstacle = true;
					this->myNodes[x * COL + y].isVisited = true;
				}
				else
				{
					this->myNodes[x * COL + y].isObstacle = false;
					this->myNodes[x * COL + y].isVisited = false;
				}
			}
		}
	}
	void UpdateNeighbours()
	{
		for (int x = 0; x < COL; x++)
		{
			for (int y = 0; y < COL; y++)
			{
				if (y > 0 && !this->myNodes[y * COL + x].isObstacle)
				{
					this->myNodes[y * COL + x].neighbours.push_back(&this->myNodes[(y - 1) * COL + (x + 0)]);
				}
				if (y < COL - 1 && !this->myNodes[y * COL + x].isObstacle)
				{
					this->myNodes[y * COL + x].neighbours.push_back(&this->myNodes[(y + 1) * COL + (x + 0)]);
				}
				if (x > 0 && !this->myNodes[y * COL + x].isObstacle)
				{
					this->myNodes[y * COL + x].neighbours.push_back(&this->myNodes[(y + 0) * COL + (x - 1)]);
				}
				if (x < COL - 1 && !this->myNodes[y * COL + x].isObstacle)
				{
					this->myNodes[y * COL + x].neighbours.push_back(&this->myNodes[(y + 0) * COL + (x + 1)]);
				}
			}
		}
	}

	void UpdatePlayerNode()
	{
		glm::vec2 playerIndex = playerPtr->change_maze_according_to_player_pos();
		int x = playerIndex.x;
		int y = playerIndex.y;
		this->startNode = &myNodes[x * COL + y];
	}

	void UpdateEnemyNode(glm::vec2& enemyIndex)
	{
		int x = enemyIndex.x;
		int y = enemyIndex.y;

		this->endNode = &myNodes[x * COL + y];
	}

	void Update(glm::vec2& enemyPos)
	{
		UpdateAllNodes();
		UpdateNeighbours();
		UpdatePlayerNode();
		UpdateEnemyNode(enemyPos);
		Solve_AStar();
	}

	bool Solve_AStar()
	{
		// Reset Navigation Graph - default all node states

		auto distance = [](Node* a, Node* b)
		{
			return sqrtf((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y));
		};

		auto heuristic = [distance](Node* a, Node* b)
		{
			return distance(a, b);
		};

		Node* nodeCurrent = this->startNode;
		this->startNode->g_score = 0.0f;
		this->startNode->f_score = heuristic(this->startNode, this->endNode);


		list<Node*> listNotTestedNodes;
		listNotTestedNodes.push_back(startNode);


		while (!listNotTestedNodes.empty() && nodeCurrent != endNode)// Find absolutely shortest path // && nodeCurrent != nodeEnd)
		{
			listNotTestedNodes.sort([](const Node* lhs, const Node* rhs) { return lhs->f_score < rhs->f_score; });

			while (!listNotTestedNodes.empty() && listNotTestedNodes.front()->isVisited)
			{
				listNotTestedNodes.pop_front();
			}

			if (listNotTestedNodes.empty())
			{
				break;
			}
			nodeCurrent = listNotTestedNodes.front();
			nodeCurrent->isVisited = true;


			for (auto nodeNeighbour : nodeCurrent->neighbours)
			{
				if (!nodeNeighbour->isVisited && nodeNeighbour->isObstacle == 0)
				{
					listNotTestedNodes.push_back(nodeNeighbour);
				}

				float fPossiblyLowerGoal = nodeCurrent->g_score + distance(nodeCurrent, nodeNeighbour);

				if (fPossiblyLowerGoal < nodeNeighbour->g_score)
				{
					nodeNeighbour->parent = nodeCurrent;
					nodeNeighbour->g_score = fPossiblyLowerGoal;

					nodeNeighbour->f_score = nodeNeighbour->g_score + heuristic(nodeNeighbour, endNode);
					//cout << nodeNeighbour->x << " " << nodeNeighbour->y << "\n";
				}
			}
		}

		return true;
	}
};

class Enemy : public Entity, public Node
{
private:

	int* myMaze;
	int* tempMaze;
	Player* myPlayer_ptr;
	A_Star_Path* aStar;
	int enemyID;

	float ii = 0.0f;
	int prev_i;
	int prev_j;

public:
	glm::vec2 getIndex()
	{
		int i = int(glm::round(this->getPosition().x)) / 2;
		int j = int(glm::round(this->getPosition().z)) / 2;

		if (i != prev_i || j != prev_j)
		{
			myMaze[prev_i * COL + prev_j] = tempMaze[prev_i * COL + prev_j];
		}

		if ((i != 0 && i != COL - 1) && (j != 0 && j != COL - 1))
		{
			prev_i = i;
			prev_j = j;
		}

		return glm::vec2(prev_i, prev_j);
	}

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

	vector<string>animation;
	int animIter = 0;
	vector<Model>animModels;
	int counter = 0;

	double getDistance(glm::vec3 p1, glm::vec3 p2)
	{
		return abs(sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y) + (p1.z - p2.z) * (p1.z - p2.z)));
	}

	void calculatePlayer()
	{
		if (isActive)
		{
			if (timePassed > 0.30f)
			{
				if (aaa)
				{
					glm::vec2 enemyIndex;
					enemyIndex.y = round(this->getIndex().x);
					enemyIndex.x = round(this->getIndex().y);
					aStar->Update(enemyIndex);
					currentNode = aStar->endNode;
					aaa = 1;
				}
				if ((round(this->getIndex().y) * 2 == (currentNode->x * 2.0f)) &&
					(round(this->getIndex().x) * 2 == (currentNode->y * 2.0f)))
				{
					glm::vec3 t = glm::vec3(round(this->getIndex().x) * 2, 0.0f , round(this->getIndex().y) * 2);
					t.y = -0.4f;
					this->setPosition(t);

					int x;
					int z;
					if (currentNode != aStar->startNode && currentNode != nullptr)
					{
						x = round(this->getIndex().y) * 2;
						z = round(this->getIndex().x) * 2;


						currentNode = currentNode->parent;
						if (currentNode != nullptr)
						{
							posDiff = glm::vec3((currentNode->y * 2.0f) - z, 0.0f , (currentNode->x * 2.0f) - x);

							/*cout << currentNode->x * 2.0f << " ";
							cout << currentNode->y * 2.0f << "| ";
							cout << round(this->getPosition().z) << " ";
							cout << round(this->getPosition().x) << "| ";
							cout << x << " ";
							cout << z << "\n";*/
						}
					}
				}
				timePassed = 0.0f;
				
			}
			else
			{
				glm::vec3 temp = this->getPosition();
				temp += posDiff * (this->velocity * (*this->deltaTime));
				/*temp += posDiff;
				posDiff = glm::vec3(0, 0, 0);*/

				if (posDiff.x == 0.0f && posDiff.z == -2.0f)
				{
					angle = 180.0f;
				}
				else if (posDiff.x == 0.0f && posDiff.z == 2.0f)
				{
					angle = 0.0f;
				}
				else if (posDiff.x == 2.0f && posDiff.z == 0.0f)
				{
					angle = 90.0f;
				}
				else if (posDiff.x == -2.0f && posDiff.z == 0.0f)
				{
					angle = 270.0f;
				}
				//cout << posDiff.x << " " << posDiff.z << "\n";

				temp.y = -0.4f;
				this->setPosition(temp);
			}
			this->timePassed += *this->deltaTime;
			
			animate();
			
		}
		else
		{
			if (getDistance(myPlayer_ptr->getPosition(), this->getPosition())<=15.0f && myPlayer_ptr->getJumpStatus())
			{
				this->isActive = true;
			}
		}
	}

private:
	void animate()
	{
		if (counter >= 10)
		{
			setModel(&animModels[animIter]);
			animIter++;
			if (animIter >= animModels.size())
			{
				this->animIter = 1;
			}
			counter = 0;
		}
		else
		{
			counter++;
		}
	}

public:
	Enemy(const char* vertexShader, const char* fragmentShader, vector<string>&model,
		glm::vec3 position, int id, float* dlTime,
		Player* player_ptr, int* maze)
		: Entity(vertexShader, fragmentShader, model[0], glm::vec3(0.60f, 0.60f, 0.60f))
	{
		this->myPlayer_ptr = player_ptr;
		this->aStar = new A_Star_Path(player_ptr, maze);
		this->myMaze = maze;
		this->deltaTime = dlTime;
		this->setPosition(position);
		this->setMaze();
		this->setId(id);
		setAnimation(model);
	}
	// deep copy
	/*
	Enemy(const Enemy& other)
	{
		this->myPlayer_ptr = other.myPlayer_ptr;
		this->aStar = new A_Star_Path(other.myPlayer_ptr, other.myMaze);
		this->myMaze = other.myMaze;
		this->deltaTime = other.deltaTime;
		this->position = other.position;
		this->setMaze();
		this->setId(other.getId());
		this->myShader = other.myShader;
		this->myModel = other.myModel;
	}
	*/

	~Enemy()
	{

	}


	void Update()
	{
		calculatePlayer();
	}

public:
	void setId(int id)
	{
		this->enemyID = id;
	}

	int getId() const
	{
		return this->enemyID;
	}

	void setMaze()
	{
		this->tempMaze = new int[COL * COL];
		for (unsigned int i = 0; i < COL; i++)
		{
			for (unsigned int j = 0; j < COL; j++)
			{
				this->tempMaze[i * COL + j] = this->myMaze[i * COL + j];
			}
		}
	}

	void setActive(bool active = true)
	{
		this->isActive = active;
	}

	bool getActive()
	{
		return this->isActive;
	}

	void setAnimation(vector<string>& s)
	{
		this->animation = s;
	}

	void setAnimModel()
	{
		for (int i = 0; i < animation.size(); i++)
		{
			Model temp(animation[i]);
			animModels.push_back(temp);
		}
		//cout << animModels.size() << endl;
	}
};

