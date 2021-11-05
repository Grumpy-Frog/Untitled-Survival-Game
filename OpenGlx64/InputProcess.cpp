#include "InputProcess.h"


bool InputProcess::checkCollision(Player& myPlayer, Hedge& myHedges)
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

	return true;
}

void InputProcess::MoveFront(Player& myPlayer, Camera& camera,
	Hedge& myHedges, float velocity)
{
	bool moveXPosition = true;
	bool moveZPosition = true;
	glm::vec3 prevPos = myPlayer.getPosition();
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
	//cout << moveXPosition << " " << moveZPosition << endl;
	//cout << camera.Position.x << " " << camera.Position.y << endl;
	myPlayer.setPosition(camera.Position);
}

void InputProcess::MoveRight(Player& myPlayer, Camera& camera,
	Hedge& myHedges, float velocity)
{
	bool moveXPosition = 1;
	bool moveZPosition = 1;
	glm::vec3 prevPos = myPlayer.getPosition();

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

InputProcess::InputProcess(const GLFWvidmode* mode)
{
	// pass
	// will add something in future
	this->lastX = mode->width / 2.0f;
	this->lastY = mode->height / 2.0f;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void InputProcess::processInputKeyboard(GLFWwindow* window, Camera& camera, Player& myPlayer, Hedge& myHedges,
	float deltaTime, glm::vec3* posLight)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		//glfwSetWindowShouldClose(window, true);
		return;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
		glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
	{
		myPlayer.setSpeed(7.5f);
		myPlayer.setJumpStatus(true);
	}
	else
	{
		myPlayer.setSpeed(3.5f);
		myPlayer.setJumpStatus(false);
	}

	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	{
		posLight[3] = camera.Position;
		myPlayer.setTorchStatus(true);
	}
	else
	{
		posLight[3] = glm::vec3(2500.0f, 2500.0f, 2500.0f);
		myPlayer.setTorchStatus(0);
	}



	float velocity = myPlayer.getSpeed() * deltaTime;


	if (this->isJumping == false && this->isFalling == false)
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			MoveFront(myPlayer, camera, myHedges, velocity);
			myPlayer.setWalking(true);
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			MoveFront(myPlayer, camera, myHedges, -velocity);
			myPlayer.setWalking(true);
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			MoveRight(myPlayer, camera, myHedges, velocity);
			myPlayer.setWalking(true);
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			MoveRight(myPlayer, camera, myHedges, -velocity);
			myPlayer.setWalking(true);
		}
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && camera.Position.y <= 1.0f)
	{
		this->jumpVelocity = 5.0f;
		this->isJumping = true;
		myPlayer.setJumpStatus(this->isJumping);
		myPlayer.setSoundState(3);
	}
	else
	{
		myPlayer.setSoundState(0);
	}

	if (this->isJumping)
	{
		calculateJump(camera, deltaTime);
	}
	else if (this->isFalling)
	{
		this->jumpVelocity += gravity * deltaTime;
		camera.Position.y -= this->jumpVelocity * deltaTime;
	}

	if (camera.Position.y < 1.0f)
	{
		camera.Position.y = 1.0f;
		this->isJumping = false;
		this->isFalling = false;
		myPlayer.setJumpStatus(this->isJumping);
	}
}

void InputProcess::calculateJump(Camera& camera, float& deltaTime)
{
	this->jumpVelocity -= gravity * deltaTime;
	camera.Position.y += this->jumpVelocity * deltaTime;

	if (camera.Position.y >= 4.0f)
	{
		this->jumpVelocity = 0.0f;
		this->isJumping = false;
		this->isFalling = true;
	}
}

void InputProcess::processInputGamePad(GLFWwindow* window, Camera& camera, Player& myPlayer, Hedge& myHedges,
	float deltaTime, glm::vec3* posLight)
{
	int axesCount;
	const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);

	if (defaultAxesValue == 0.0f)
	{
		defaultAxesValue = axes[2];
	}

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
	{
		//glfwSetWindowShouldClose(window, true);
	}

	if (GLFW_PRESS == buttons[5])
	{
		myPlayer.setSpeed(7.5f);
		myPlayer.setJumpStatus(true);
	}
	else
	{
		myPlayer.setSpeed(3.5f);
		myPlayer.setJumpStatus(false);
	}


	if (GLFW_PRESS == buttons[6])
	{
		posLight[3] = camera.Position;
		myPlayer.setTorchStatus(1);
	}
	else
	{
		posLight[3] = glm::vec3(2500.0f, 2500.0f, 2500.0f);
		myPlayer.setTorchStatus(0);
	}



	float velocity = myPlayer.getSpeed() * deltaTime;

	if (this->isJumping == false && this->isFalling == false)
	{
		///Player Movement
		if (axes[1] == -1.0f /*|| GLFW_PRESS == buttons[12] */)
		{
			MoveFront(myPlayer, camera, myHedges, velocity);
			myPlayer.setWalking(true);
		}
		if (axes[1] == 1.0f /*|| GLFW_PRESS == buttons[14] */)
		{
			MoveFront(myPlayer, camera, myHedges, -velocity);
			myPlayer.setWalking(true);
		}
		if (axes[0] == 1.0f /*|| GLFW_PRESS == buttons[13] */)
		{
			MoveRight(myPlayer, camera, myHedges, velocity);
			myPlayer.setWalking(true);
		}
		if (axes[0] == -1.0f /*|| GLFW_PRESS == buttons[15] */)
		{
			MoveRight(myPlayer, camera, myHedges, -velocity);
			myPlayer.setWalking(true);
		}
	}

	//camera.Position.y = 1.0f;

	if (GLFW_PRESS == buttons[4] && camera.Position.y <= 1.0f)
	{
		this->jumpVelocity = 5.0f;
		this->isJumping = true;
		myPlayer.setJumpStatus(this->isJumping);
		myPlayer.setSoundState(3);
	}
	else
	{
		myPlayer.setSoundState(0);
	}

	if (this->isJumping)
	{
		calculateJump(camera, deltaTime);
	}
	else if (this->isFalling)
	{
		this->jumpVelocity += gravity * deltaTime;
		camera.Position.y -= this->jumpVelocity * deltaTime;
	}
	if (camera.Position.y < 1.0f)
	{
		camera.Position.y = 1.0f;
		this->isJumping = false;
		this->isFalling = false;
		myPlayer.setJumpStatus(this->isJumping);
	}


	if (axes[2] != defaultAxesValue)
	{
		xpos += 10.0f * axes[2];
	}
	if (axes[3] != defaultAxesValue)
	{
		ypos += 10.0f * axes[3];
	}
	axes_callback(camera);

}

void InputProcess::axes_callback(Camera& camera)
{
	if (firstAxes)
	{
		lastX = xpos;
		lastY = ypos;
		firstAxes = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}