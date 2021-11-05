#ifndef CUBECOLLIDER_H
#define CUBECOLLIDER_H


#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


#include "Player.h"
#include "Enemy.h"

#include <cmath>
#include <vector>
#include <random>
#include <utility>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <algorithm>

class CubeCollider
{
private:
	glm::vec3 colliderPosition;

	glm::vec3 AAABBB;

public:

	CubeCollider(glm::vec3& position);

	void setPosition(glm::vec3& position);

	glm::vec3 getPosition();
};

class CollisionDetection
{
public:
	CollisionDetection();

	bool SphereRectCollision(Player& sphere, CubeCollider& rect);
	
	bool SphereSphereCollision(Player& sphere1, Enemy& sphere2);
};




#endif //CUBECOLLIDER_H