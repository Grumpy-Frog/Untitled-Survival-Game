#include "Enemy.h"

// Node class
Node::Node()
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

Node::~Node()
{

}

// A_Star_Class

A_Star_Path::A_Star_Path(Player* player, int* maze)
{
	this->playerPtr = player;
	this->myMaze = maze;
	this->myNodes = new Node[COL * COL];
	UpdateAllNodes();
	UpdateNeighbours();
}

A_Star_Path::~A_Star_Path()
{
	this->myNodes = NULL;
	this->startNode = NULL;
	this->endNode = NULL;
	this->playerPtr = NULL;
}

void A_Star_Path::UpdateAllNodes()
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

void A_Star_Path::UpdateNeighbours()
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

void A_Star_Path::UpdatePlayerNode()
{
	glm::vec2 playerIndex = playerPtr->change_maze_according_to_player_pos();
	int x = playerIndex.x;
	int y = playerIndex.y;
	this->startNode = &myNodes[x * COL + y];
}

void A_Star_Path::UpdateEnemyNode(glm::vec2& enemyIndex)
{
	int x = enemyIndex.x;
	int y = enemyIndex.y;

	this->endNode = &myNodes[x * COL + y];
}

void A_Star_Path::Update(glm::vec2& enemyPos)
{
	UpdateAllNodes();
	UpdateNeighbours();
	UpdatePlayerNode();
	UpdateEnemyNode(enemyPos);
	Solve_AStar();
}

bool A_Star_Path::Solve_AStar()
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



//Enemy

double Enemy::getDistance(glm::vec3 p1, glm::vec3 p2)
{
	return abs(sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y) + (p1.z - p2.z) * (p1.z - p2.z)));
}

void Enemy::calculatePlayer()
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
				glm::vec3 t = glm::vec3(round(this->getIndex().x) * 2, 0.0f, round(this->getIndex().y) * 2);
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
						posDiff = glm::vec3((currentNode->y * 2.0f) - z, 0.0f, (currentNode->x * 2.0f) - x);

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

		myAnimation1->animate(*(this));

	}
	else
	{
		if ((getDistance(myPlayer_ptr->getPosition(), this->getPosition()) <= 15.0f) &&
			(myPlayer_ptr->getJumpStatus() || myPlayer_ptr->getTorchStatus()))
		{
			if (this->isActive == false)
			{
				this->setActive(true);
			}
		}
	}
}

void Enemy::initRoarAudio(const char* s)
{
	this->enemyRoarAudio = SoundEffectsLibrary::Get()->Load(s);
}

void Enemy::playSound()
{
	this->enemySoundPlayer->SetLooping(true);
	this->enemySoundPlayer->Play(this->enemyRoarAudio);
}

void Enemy::StopSound()
{
	this->enemySoundPlayer->Stop();
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

Enemy::~Enemy()
{
	//this->enemySoundPlayer.Stop();
	//this->enemySoundPlayer.~SoundEffectsPlayer();
	//delete this->enemySoundPlayer;

	this->myPlayer_ptr = NULL;
	this->aStar = NULL;
	this->enemySoundPlayer = NULL;
	this->activationSoundPlayer = NULL;
}

glm::vec2 Enemy::getIndex()
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

void Enemy::deallocEnem()
{
	if (this->aStar)
	{
		delete this->aStar;
	}
	if (this->tempMaze)
	{
		delete this->tempMaze;
	}

	if (this->enemySoundPlayer->isPlaying())
	{
		this->enemySoundPlayer->Stop();
	}
}


void Enemy::Update(glm::mat4& projection, glm::mat4& view, Camera& camera,float &deltaTime, glm::vec3* pointLights)
{
	calculatePlayer();
	this->UpdateLighting(projection, view, camera, *this->myShader,deltaTime, pointLights);
	this->Render(projection, view, camera);

	if (this->getActive() == true)
	{
		this->enemySoundPlayer->SetPosition(this->getPosition().x, this->getPosition().y, this->getPosition().z);
	}

	if (this->getActive() == true)
	{
		if (this->enemySoundPlayer->isPlaying() == false)
		{
			this->enemySoundPlayer->Play(this->enemyRoarAudio);
		}
	}
}

void Enemy::setId(int id)
{
	this->enemyID = id;
}

int Enemy::getId() const
{
	return this->enemyID;
}

void Enemy::setMaze()
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

void Enemy::setActive(bool active)
{
	if (this->isActive == false)
	{
		this->isActive = active;
		this->playSound();
		this->activationSoundPlayer->Play(this->activationSound);
	}
}

bool Enemy::getActive()
{
	return this->isActive;
}

Animation* Enemy::getAnimation()
{
	return this->myAnimation1;
}