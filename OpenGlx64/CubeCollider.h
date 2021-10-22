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

	CubeCollider(glm::vec3& position)
	{
		this->colliderPosition = position;
		this->AAABBB = glm::vec3(1.0f, 1.0f, 1.0f);
	}

	void setPosition(glm::vec3& position)
	{
		this->colliderPosition = position;
	}

	glm::vec3 getPosition()
	{
		return this->colliderPosition;
	}
};

class CollisionDetection
{
public:
	CollisionDetection()
	{

	}

	bool SphereRectCollision(Player& sphere, CubeCollider& rect)
	{
		float sphereXDistance = abs(sphere.getPosition().x - rect.getPosition().x);
		float sphereYDistance = abs(sphere.getPosition().y - rect.getPosition().y);
		float sphereZDistance = abs(sphere.getPosition().z - rect.getPosition().z);

		if (sphereXDistance >= (1.0f + sphere.getRadious())) { return false; }
		if (sphereYDistance >= (1.0f + sphere.getRadious())) { return false; }
		if (sphereZDistance >= (1.0f + sphere.getRadious())) { return false; }

		if (sphereXDistance < (1.0f)) { return true; }
		if (sphereYDistance < (1.0f)) { return true; }
		if (sphereZDistance < (1.0f)) { return true; }

		float cornerDistance_sq = ((sphereXDistance - 1.0f) * (sphereXDistance - 1.0f)) +
			((sphereYDistance - 1.0f) * (sphereYDistance - 1.0f) +
				((sphereYDistance - 1.0f) * (sphereYDistance - 1.0f)));

		return (cornerDistance_sq < (sphere.getRadious()* sphere.getRadious()));
	}

	bool SphereSphereCollision(Player& sphere1, Enemy& sphere2)
	{
		float distance = sqrt(
			(sphere1.getPosition().x - sphere2.getPosition().x) * (sphere1.getPosition().x - sphere2.getPosition().x) +
			(sphere1.getPosition().y - sphere2.getPosition().y) * (sphere1.getPosition().y - sphere2.getPosition().y) +
			(sphere1.getPosition().z - sphere2.getPosition().z) * (sphere1.getPosition().z - sphere2.getPosition().z));
		bool x = distance < (sphere1.getRadious() + sphere2.getRadious());
		//cout << distance << " " << x << endl;
		return distance < (sphere1.getRadious() + sphere2.getRadious());
	}
};




#endif //CUBECOLLIDER_H