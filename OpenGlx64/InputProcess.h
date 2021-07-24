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
	void processInputKeyboard(GLFWwindow* window, Camera& camera, Player& myPlayer, Hedge& myHedges, float deltaTime)
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


	void processInputGamePad(GLFWwindow* window, Camera& camera, Player& myPlayer, Hedge& myHedges, float deltaTime)
	{
		int axesCount;
		const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);

		///system("cls");
		///cout << "Left X: " << axes[0] << "\n";
		///cout << "Left Y: " << axes[1] << "\n";
		///cout << "Right X: " << axes[2] << "\n";
		///cout << "Right Y: " << axes[3] << "\n";

		int buttonCount;
		const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);

		/*
		if (GLFW_PRESS == buttons[0])
		{
			cout << "X\n";
		}
		if (GLFW_PRESS == buttons[1])
		{
			cout << "A\n";
		}
		if (GLFW_PRESS == buttons[2])
		{
			cout << "B\n";
		}
		if (GLFW_PRESS == buttons[3])
		{
			cout << "Y\n";
		}
		if (GLFW_PRESS == buttons[4])
		{
			cout << "LB\n";
		}
		if (GLFW_PRESS == buttons[5])
		{
			cout << "RB\n";
		}
		if (GLFW_PRESS == buttons[6])
		{
			cout << "LT\n";
		}
		if (GLFW_PRESS == buttons[7])
		{
			cout << "RT\n";
		}
		if (GLFW_PRESS == buttons[8])
		{
			cout << "Back\n";
		}
		if (GLFW_PRESS == buttons[9])
		{
			cout << "Start\n";
		}
		if (GLFW_PRESS == buttons[10])
		{
			cout << "Left_AXES_PUSH\n";
		}
		if (GLFW_PRESS == buttons[11])
		{
			cout << "Right_AXES_PUSH\n";
		}
		if (GLFW_PRESS == buttons[12])
		{
			cout << "Up\n";
		}
		if (GLFW_PRESS == buttons[13])
		{
			cout << "Right\n";
		}
		if (GLFW_PRESS == buttons[14])
		{
			cout << "Down\n";
		}
		if (GLFW_PRESS == buttons[15])
		{
			cout << "Left\n";
		}
		*/



		if (buttons[8] == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);


		float velocity = 10.f * deltaTime;
		glm::vec3 prevPos;
		bool moveXPosition = 1;
		bool moveZPosition = 1;
		if (axes[1] == -1.0f)
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
		if (axes[1] == 1.0f)
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
		if (axes[0] == 1.0f)
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
		if (axes[0] == -1.0f)
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
