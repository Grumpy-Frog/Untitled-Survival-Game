#ifndef CUBECOLLIDER_H
#define CUBECOLLIDER_H

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <vector>

class CubeCollider 
{
private:
	glm::vec3 colliderPosition;

	glm::vec3 AAABBB;

public:

	CubeCollider(glm::vec3 &position)
	{
		this->colliderPosition = position;
		this->AAABBB = glm::vec3(1.0f, 1.0f, 1.0f);
	}

	void setPosition(glm::vec3 &position)
	{
		this->colliderPosition = position;
	}

	glm::vec3 getPosition()
	{
		return this->colliderPosition;
	}
};



#endif //CUBECOLLIDER_H