#ifndef INPUTPROCESS_H
#define INPUTPROCESS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>

#include "Camera.h"
#include "Player.h"
#include "Hedge.h"
#include "CubeCollider.h"

using namespace std;


class InputProcess
{
private:

	bool checkCollision(Player& myPlayer, Hedge& myHedges)
	{
		CollisionDetection myCollisionChecker;
		auto iter = myHedges.getColliders();
		for (auto it : iter)
		{
			if (myCollisionChecker.SphereRectCollision(myPlayer, it))
			{
				return false;
			}
		}
	}

public:
	InputProcess()
	{
		// pass
		// will add something in future
	}


	// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
	// ---------------------------------------------------------------------------------------------------------
	void processInput(GLFWwindow* window, Camera& camera, Player& myPlayer, Hedge& myHedges, float deltaTime)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);


		float velocity = 10.f * deltaTime;
		glm::vec3 prevPos;
		bool moveXPosition = 1;
		bool moveZPosition = 1;
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			prevPos = myPlayer.getPosition();
			glm::vec3 newPos = glm::vec3(camera.Position.x + camera.Front.x * velocity,
				myPlayer.getPosition().y, myPlayer.getPosition().z);
			myPlayer.setPosition(newPos);
			
			moveXPosition = checkCollision(myPlayer, myHedges);
			
			myPlayer.setPosition(prevPos);

			newPos = glm::vec3(myPlayer.getPosition().x,
				myPlayer.getPosition().y, camera.Position.z + camera.Front.z * velocity);
			myPlayer.setPosition(newPos);
			
			moveZPosition = checkCollision(myPlayer, myHedges);

			myPlayer.setPosition(prevPos);
			if (moveXPosition)
			{
				camera.Position.x += camera.Front.x * velocity;
			}
			if (moveZPosition)
			{
				camera.Position.z += camera.Front.z * velocity;
			}
			myPlayer.setPosition(camera.Position);
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			prevPos = myPlayer.getPosition();
			moveXPosition = 1;
			moveZPosition = 1;
			glm::vec3 newPos = glm::vec3(camera.Position.x + -camera.Front.x * velocity,
				myPlayer.getPosition().y, myPlayer.getPosition().z);
			myPlayer.setPosition(newPos);
			
			moveXPosition = checkCollision(myPlayer, myHedges);

			myPlayer.setPosition(prevPos);
			newPos = glm::vec3(myPlayer.getPosition().x,
				myPlayer.getPosition().y, camera.Position.z + -camera.Front.z * velocity);
			myPlayer.setPosition(newPos);
			
			moveZPosition = checkCollision(myPlayer, myHedges);

			myPlayer.setPosition(prevPos);
			if (moveXPosition)
			{
				camera.Position.x += -camera.Front.x * velocity;
			}
			if (moveZPosition)
			{
				camera.Position.z += -camera.Front.z * velocity;
			}
			myPlayer.setPosition(camera.Position);
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			prevPos = myPlayer.getPosition();
			moveXPosition = 1;
			moveZPosition = 1;
			glm::vec3 newPos = glm::vec3(camera.Position.x + camera.Right.x * velocity,
				myPlayer.getPosition().y, myPlayer.getPosition().z);
			myPlayer.setPosition(newPos);
			
			moveXPosition = checkCollision(myPlayer, myHedges);

			myPlayer.setPosition(prevPos);
			newPos = glm::vec3(myPlayer.getPosition().x,
				myPlayer.getPosition().y, camera.Position.z + camera.Right.z * velocity);
			myPlayer.setPosition(newPos);
			
			moveZPosition = checkCollision(myPlayer, myHedges);

			myPlayer.setPosition(prevPos);
			if (moveXPosition)
			{
				camera.Position.x += camera.Right.x * velocity;
			}
			if (moveZPosition)
			{
				camera.Position.z += camera.Right.z * velocity;
			}
			myPlayer.setPosition(camera.Position);
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			prevPos = myPlayer.getPosition();
			moveXPosition = 1;
			moveZPosition = 1;
			glm::vec3 newPos = glm::vec3(camera.Position.x + -camera.Right.x * velocity,
				myPlayer.getPosition().y, myPlayer.getPosition().z);
			myPlayer.setPosition(newPos);

			moveXPosition = checkCollision(myPlayer, myHedges);
			
			myPlayer.setPosition(prevPos);
			newPos = glm::vec3(myPlayer.getPosition().x,
				myPlayer.getPosition().y, camera.Position.z + -camera.Right.z * velocity);
			myPlayer.setPosition(newPos);
			
			moveZPosition = checkCollision(myPlayer, myHedges);

			myPlayer.setPosition(prevPos);
			if (moveXPosition)
			{
				camera.Position.x += -camera.Right.x * velocity;
			}
			if (moveZPosition)
			{
				camera.Position.z += -camera.Right.z * velocity;
			}
			myPlayer.setPosition(camera.Position);
		}

		camera.Position.y = 1.0f;
	}
};

#endif //INPUTPROCESS_H
