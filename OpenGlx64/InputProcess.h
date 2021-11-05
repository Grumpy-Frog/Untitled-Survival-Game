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
	float lastX = (float)1920.0f / 2.0f;
	float lastY = (float)1080.0f / 2.0f;
	float xpos = 0.0f;
	float ypos = 0.0f;
	double defaultAxesValue = 0.0f;
	bool firstAxes = false;


	//Jump variables
	float gravity = 6.81f;
	bool isJumping = false;
	bool isFalling = false;
	float jumpFriction = 0.5f;
	float jumpVelocity = 0.0f;

private:

	bool checkCollision(Player& myPlayer, Hedge& myHedges);

	void MoveFront(Player& myPlayer, Camera& camera,
		Hedge& myHedges, float velocity);

	void MoveRight(Player& myPlayer, Camera& camera,
		Hedge& myHedges, float velocity);

public:
	InputProcess(const GLFWvidmode* mode);

	// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
	// ---------------------------------------------------------------------------------------------------------
	void processInputKeyboard(GLFWwindow* window, Camera& camera, Player& myPlayer, Hedge& myHedges,
		float deltaTime, glm::vec3* posLight);

	void calculateJump(Camera& camera, float& deltaTime);

	void processInputGamePad(GLFWwindow* window, Camera& camera, Player& myPlayer, Hedge& myHedges,
		float deltaTime, glm::vec3* posLight);

	void axes_callback(Camera& camera);
};

#endif //INPUTPROCESS_H
