#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <stb_image.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "Player.h"
#include "Enemy.h"
#include "Hedge.h"
#include "Shader.h"
#include "model.h"
#include "Mesh.h"
#include "MazeGenerator.h"
#include "Camera.h"
#include "InputProcess.h"
#include "Math.h"
#include "Button.h"
#include "LightCube.h"
#include "Extra.h"


#include "OpenAL/SoundDevice.h"
#include "OpenAL/SoundEffectsPlayer.h"
#include "OpenAL/SoundEffectsLibrary.h"


#include <iostream>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
//#include <conio.h>


#ifdef _WIN32
#include <windows.h>
//extern "C" __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
//extern "C" __declspec(dllexport) DWORD AmdPowerXpressRequestHighPerformance = 0x00000001;
#endif


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

// camera
Camera camera(glm::vec3(2.0f, 1.0f, 2.0f));
float lastX = (float)SCR_WIDTH / 2.0;
float lastY = (float)SCR_HEIGHT / 2.0;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

void menuCameraFixedPosition()
{
	camera.Position.x = 17.3304f;
	camera.Position.y = 13.4258f;
	camera.Position.z = 15.0817f;
	camera.Front.x = -0.682428f;
	camera.Front.y = -0.438371f;
	camera.Front.z = -0.584912f;
	camera.Pitch = 0.0f;
}

void creditCameraFixedPosition()
{
	camera.Position.x = 1.59869f;
	camera.Position.y = 19.7325f;
	camera.Position.z = -8.03981f;
	camera.Front.x = 0.0114171f;
	camera.Front.y = -0.837719f;
	camera.Front.z = 0.545983f;
	//camera.Pitch = 0.0f;
}

void controlCameraFixedPosition()
{
	camera.Position.x = -11.657f;
	camera.Position.y = 14.4806f;
	camera.Position.z = -11.297f;
	camera.Front.x = 0.601058f;
	camera.Front.y = -0.617035f;
	camera.Front.z = 0.507934f;
	camera.Pitch = 0.0f;
}

void matchEndCameraFixedPosition()
{
	camera.Position.x = 59.4987f;
	camera.Position.y = 10.9417f;
	camera.Position.z = 60.5954f;
	camera.Front.x = -0.696269f;
	camera.Front.y = -0.0505934f;
	camera.Front.z = -0.715996f;
	camera.Pitch = 0.0f;
}

std::string exec(const char* cmd)
{
	char buffer[128];
	std::string result = "";
	FILE* pipe = _popen(cmd, "r");
	if (!pipe) throw std::runtime_error("popen() failed!");
	try {
		while (fgets(buffer, sizeof buffer, pipe) != NULL) {
			result += buffer;
		}
	}
	catch (...) {
		_pclose(pipe);
		throw;
	}
	_pclose(pipe);
	return result;
}

void checkAuthentication()
{
	string myUUID = "39444335-3431-3030-3752-C46516A4C082"; //rafi
	//string myUUID = "F3887398-BA56-49CA-92C4-4C9E4C159A94"; // fateen
	//string myUUID = "73C28570-CEE9-0000-0000-000000000000"; // mahmud

	string result = exec("wmic path win32_computersystemproduct get uuid");
	string newResult = "";
	for (int i = result.size() - 7, j = 0; j < 36; i--, j++)
	{
		newResult += result[i];
		//cout<<result[i]<<"X\n";
	}
	reverse(newResult.begin(), newResult.end());

	//cout << myUUID.size() << endl;
	//cout << newResult.size() << endl;
	//cout << myUUID << endl;
	//cout << newResult << endl;
	if (strcmp(myUUID.c_str(), newResult.c_str()) == 0)
	{
		cout << "YES\n";
	}
	else
	{
		cout << "NO\n";
		MessageBox
		(
			NULL,
			(LPCWSTR)L" It seems like you are not Syed Fateen Navid Hyder \n\n Please contact\n Email: rafihassan@iut-dhaka.edu\n Contact No: +8801701459732\n",
			(LPCWSTR)L"Owner Authentication Error!",
			MB_ICONHAND | MB_DEFBUTTON2
		);
		cout << "Please buy this game from Rafi Hassan Chowdhury\nrafihassan@iut-dhaka.edu\n+8801701459732\n";
		exit(1);
		return;
	}
}

void matchEndText(GLFWwindow* window, const GLFWvidmode* mode, string modelName, const char* soundName)
{
	float degree = 0;
	Button matchEndText("menuShaderVertex.shader", "menuShaderFragment.shader", modelName);
	glm::vec3 pos = glm::vec3(matchEndText.getPosition().x, matchEndText.getPosition().y - 2.5f, matchEndText.getPosition().z);
	matchEndText.setPosition(pos);
	matchEndCameraFixedPosition();
	float xVel = -6.95619f;
	float yVel = -0.505446f;
	float zVel = -7.1533f;

	//Sounds
	SoundDevice* sd = LISTENER->Get();
	ALint attunation = AL_INVERSE_DISTANCE_CLAMPED;
	sd->SetAttunation(attunation);

	SoundEffectsPlayer soundEffectPlayer;
	int gameEndSound = SE_LOAD(soundName);
	soundEffectPlayer.SetLooping(false);
	soundEffectPlayer.Play(gameEndSound);

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// render
		// ------
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		degree += 1.0f * deltaTime;
		if (degree > 360)
		{
			degree = 0;
		}

		pointLightPositions[0] = glm::vec3(cos(degree) * 15.f, sin(degree) * 15.0f, pointLightPositions[0].z);
		pointLightPositions[1] = glm::vec3(sin(degree) * 15.f, cos(degree) * 15.f, pointLightPositions[1].z);
		pointLightPositions[2] = glm::vec3(sin(degree) * 15.f, cos(degree) * 15.f, sin(degree) * 15.f);
		pointLightPositions[3] = glm::vec3(sin(degree) * 6.f + 1.5f, sin(degree + degree) * 5.0f + 3.0f, cos(degree) * 6.0f + 1.5f);

		//cout << camera.Position.x << " " << camera.Position.y << " " << camera.Position.z << "\n";
		//cout << camera.Front.x << " " << camera.Front.y << " " << camera.Front.z << "\n";

		camera.Position.x += xVel * deltaTime;
		camera.Position.y += yVel * deltaTime;
		camera.Position.z += zVel * deltaTime;

		soundEffectPlayer.SetPosition(camera.Position);
		sd->SetLocation(camera.Position);
		sd->SetOrientation(camera.Front.x, camera.Front.y, camera.Front.z,
			camera.Up.x, camera.Up.y, camera.Up.z);

		// configure transformation matrices
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
		glm::mat4 view = camera.GetViewMatrix();


		matchEndText.Update(projection, view, camera, 45.0f, glm::vec3(4.0f, 4.0f, 4.0f), pointLightPositions);

		if (camera.Position.x <= -11.5632f)
		{
			return;
		}

		//processInput(window);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		//glfwPollEvents();
	}
}

void gameZone(GLFWwindow* window, const GLFWvidmode* mode)
{
	bool isPlayerDead = false;

	float degree = 0.0f;
	float playTime = 0.0f;
	camera.Position = glm::vec3(34.0f, 1.0f, 2.0f);
	// build and compile shaders
	// -------------------------
	// load models
	// -----------
	// Hedge
	Hedge myHedges("lightInstanceVertex.shader", "lightInstanceFragment.shader",
		"Models/Hedge/cube.obj", "Models/Ground/cube.obj");
	myHedges.init(enemyPositions);
	int* myMazeArray;
	myMazeArray = myHedges.getMazeArray();

	/*
	for (unsigned int i = 0; i < COL; i++)
	{
		for (unsigned int j = 0; j < COL; j++)
		{
			cout << myMazeArray[i * COL + j] << " ";
		}
		cout << "\n";
	}
	*/

	// Player
	Player myPlayer("modelVertex.shader", "modelFragment.shader", "Models/Player/cube.obj",
		myMazeArray, 7.5f);
	myPlayer.setPosition(camera.Position);
	//Enemy
	vector<Enemy>myEnemies;

	vector<string>animationsModelNames;
	string modelName = "Models/CreeperForMaze/c1.obj";
	for (int i = 1; i < 6; i++)
	{
		modelName[modelName.size() - 5] = (char)(i + '0');
		animationsModelNames.push_back(modelName);
	}

	for (int i = 0; i < 4; i++)
	{
		Enemy  myEnemy1("menuShaderVertex.shader", "menuShaderFragment.shader", animationsModelNames,
			enemyPositions[i], 1, &deltaTime,
			&myPlayer, myMazeArray,
			"Audio/enemyRoar.ogg");
		myEnemy1.setRadious(2.0f);
		myEnemies.push_back(myEnemy1);
	}

	vector<LightCube>myLightCubes;
	for (int i = 0; i < 4; i++)
	{
		LightCube temp("light_cube_vertex.shader", "light_cube_fragment.shader",
			pointLightPositions[i], verticess);
		myLightCubes.push_back(temp);
	}
	myLightCubes[0].setScale(glm::vec3(4.0, 4.0, 4.0));
	pointLightPositions[1] = glm::vec3(36.0f, 100.0f, 65.0f);
	myLightCubes[1].setScale(glm::vec3(1.0, 202.0, 1.0));
	myLightCubes[1].setPosition(pointLightPositions[1]);
	pointLightPositions[2] = glm::vec3(32.0f, 100.0f, 65.0f);
	myLightCubes[2].setScale(glm::vec3(1.0, 202.0, 1.0));
	myLightCubes[2].setPosition(pointLightPositions[2]);
	pointLightPositions[3] = glm::vec3(209.0f, 0.0f, 209.0f);

	// Input System
	InputProcess myinputProcess(mode);

	//colliders
	glm::vec3 endPointPosition = glm::vec3(34.0f, 1.0f, 65.0f);
	CubeCollider endPoint(endPointPosition);
	CollisionDetection collisionDetection;

	//Sound
	SoundEffectsPlayer endPointSoundPlayer;
	int endPointMusic = SE_LOAD("Audio/endPoint.ogg");
	endPointSoundPlayer.SetPosition(endPointPosition.x, endPointPosition.y, endPointPosition.z);
	endPointSoundPlayer.SetLooping(true);
	endPointSoundPlayer.Play(endPointMusic);

	bool debug_mode = 0;
	deltaTime = 0.0f;
	lastFrame = glfwGetTime();
	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		if (playTime < 37.0f && !debug_mode)
		{
			playTime += deltaTime;
		}
		else if (debug_mode)
		{
		}
		else
		{
			for (int i = 0; i < myEnemies.size(); i++)
			{
				if (myEnemies[i].getActive() == false)
				{
					myEnemies[i].setActive(true);
				}
			}
		}


		//simple input
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS ||
			isPlayerDead ||
			collisionDetection.SphereRectCollision(myPlayer, endPoint))
		{
			if (endPointSoundPlayer.isPlaying())
			{
				endPointSoundPlayer.Stop();
			}

			for (int i = 0; i < myEnemies.size(); i++)
			{
				myEnemies[i].dealloc();
				myEnemies[i].deallocEnem();
			}
			myPlayer.dealloc();

			if (isPlayerDead)
			{
				// show death msg
				//cout << "Died\n";
				matchEndText(window, mode, "Models/lose/lose.obj", "Audio/gameOver.ogg");
			}
			if (collisionDetection.SphereRectCollision(myPlayer, endPoint))
			{
				// show win msg
				//cout << "WIN\n";
				matchEndText(window, mode, "Models/win/win.obj", "Audio/gameWon.ogg");
			}
			return;
		}


		// render
		// ------
		glClearColor((playTime / 49.0f) - 0.39f, (playTime / 49.0f) - 0.11f, (playTime / 49.0f), 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// configure transformation matrices
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
		glm::mat4 view = camera.GetViewMatrix();

		if (debug_mode)
		{

			for (int i = 0; i < myEnemies.size(); i++)
			{
				myEnemies[i].Update(projection, view, camera, pointLightPositions);
				if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS && myEnemies[3].getActive() == 0)
				{
					myEnemies[3].setActive(1);
				}
			}

			/// <summary>
			/// update all models
			/// </summary>
			/// <returns></returns>
			projection = glm::perspective(glm::radians(45.0f), (float)mode->width / (float)mode->height, 0.1f, 1000.0f);
			view = camera.GetViewMatrix();
			myHedges.update(projection, view, camera, pointLightPositions);
			myPlayer.Update(camera);

			degree += 0.5f * deltaTime;
			if (degree > 360)
			{
				degree = 0;
			}
			//lights
			pointLightPositions[0] = glm::vec3(32.0f, sin(degree) * 39.0f, cos(degree) * 39.0f + 32.0f);

			for (int i = 0; i < 3; i++)
			{
				myLightCubes[i].setPosition(pointLightPositions[i]);
				myLightCubes[i].Render(projection, view, camera, 0.0f);
			}


			if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS && 0)
			{
				system("cls");
				for (unsigned int i = 0; i < COL; i++)
				{
					for (unsigned int j = 0; j < COL; j++)
					{
						cout << myMazeArray[i * COL + j] << " ";
					}
					cout << "\n";
				}
			}



			//camera.Position.x = 28.8f;
			//camera.Position.y = 88.0f;
			//camera.Position.z = 36.0f;
			//camera.Front.x = 0.0174524f;
			//camera.Front.y = -0.999848f;
			//camera.Front.z = 7.71616e-11f;
			processInput(window);
		}
		else
		{
			for (int i = 0; i < myEnemies.size(); i++)
			{
				myEnemies[i].Update(projection, view, camera, pointLightPositions);
				if (myEnemies[i].getActive())
				{
					if (collisionDetection.SphereSphereCollision(myPlayer, myEnemies[i]))
					{
						isPlayerDead = true;
					}
				}
			}
			/// <summary>
			/// update all models
			/// </summary>
			/// <returns></returns>
			projection = glm::perspective(glm::radians(45.0f), (float)mode->width / (float)mode->height, 0.1f, 1000.0f);
			view = camera.GetViewMatrix();
			myHedges.update(projection, view, camera, pointLightPositions);
			myPlayer.Update(camera);

			degree += 0.5f * deltaTime;
			if (degree > 360)
			{
				degree = 0;
			}
			//lights
			pointLightPositions[0] = glm::vec3(32.0f, sin(degree) * 39.0f, cos(degree) * 39.0f + 32.0f);

			for (int i = 0; i < 3; i++)
			{
				myLightCubes[i].setPosition(pointLightPositions[i]);
				myLightCubes[i].Render(projection, view, camera, 0.0f);
			}

			// input
			// -----
			int present = glfwJoystickPresent(GLFW_JOYSTICK_1);
			if (present == 1)
			{
				myinputProcess.processInputGamePad(window, camera, myPlayer, myHedges, deltaTime, pointLightPositions);
			}
			myinputProcess.processInputKeyboard(window, camera, myPlayer, myHedges, deltaTime, pointLightPositions);
		}


		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

}


void controlMenu(GLFWwindow* window, const GLFWvidmode* mode)
{

	Button myButton("menuShaderVertex.shader", "menuShaderFragment.shader", "Models/Control/control.obj");

	float degree = 0;

	vector<LightCube>myLightCubes;
	for (int i = 0; i < 4; i++)
	{
		LightCube temp("light_cube_vertex.shader", "light_cube_fragment.shader",
			pointLightPositions[i], verticess);
		myLightCubes.push_back(temp);
	}

	// Player
	Button player("menuShaderVertex.shader", "menuShaderFragment.shader", "Models/pink/pink.obj");

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		controlCameraFixedPosition();

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// gamepad
		int present = glfwJoystickPresent(GLFW_JOYSTICK_1);
		if (present == 1)
		{
			int buttonCount;
			const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);
			if (GLFW_PRESS == buttons[1])
			{
				return;
			}
		}
		// keyboard input
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			return;
		}


		// render
		// ------
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// configure transformation matrices
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)mode->width / (float)mode->height, 0.1f, 1000.0f);
		glm::mat4 view = camera.GetViewMatrix();


		degree += 1.0f * deltaTime;
		if (degree > 360)
		{
			degree = 0;
		}
		pointLightPositions[0] = glm::vec3(cos(degree) * 15.f, sin(degree) * 15.0f, pointLightPositions[0].z);
		pointLightPositions[1] = glm::vec3(sin(degree) * 15.f, cos(degree) * 15.f, pointLightPositions[1].z);
		pointLightPositions[2] = glm::vec3(sin(degree) * 15.f, cos(degree) * 15.f, sin(degree) * 15.f);
		pointLightPositions[3] = glm::vec3(sin(degree) * 6.f + 1.5f, sin(degree + degree / 2.0f) * 5.0f + 7.0f, cos(degree) * 6.0f + 1.5f);

		for (int i = 0; i < 4; i++)
		{
			myLightCubes[i].setPosition(pointLightPositions[i]);
			myLightCubes[i].Render(projection, view, camera, degree * 100.0f);
		}

		player.Update(projection, view, camera, 0.0f, glm::vec3(1.0f, 1.0f, 1.0f), pointLightPositions);
		player.processInput(window, deltaTime);
		myButton.Update(projection, view, camera, 0.0f, glm::vec3(1.0f, 1.0f, 1.0f), pointLightPositions);

		processInput(window);
		//cout << camera.Position.x << " " << camera.Position.y << " " << camera.Position.z << "\n";
		//cout << camera.Front.x << " " << camera.Front.y << " " << camera.Front.z << "\n";

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void credits(GLFWwindow* window, const GLFWvidmode* mode)
{
	creditCameraFixedPosition();

	Button myButton("menuShaderVertex.shader", "menuShaderFragment.shader", "Models/Credits/credits.obj");

	float degree = 0;

	vector<LightCube>myLightCubes;
	for (int i = 0; i < 4; i++)
	{
		LightCube temp("light_cube_vertex.shader", "light_cube_fragment.shader",
			pointLightPositions[i], verticess);
		myLightCubes.push_back(temp);
	}



	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		//creditCameraFixedPosition();

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// gamepad
		int present = glfwJoystickPresent(GLFW_JOYSTICK_1);
		if (present == 1)
		{
			int buttonCount;
			const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);
			if (GLFW_PRESS == buttons[1])
			{
				return;
			}
		}
		// keyboard input
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			return;
		}


		// render
		// ------
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// configure transformation matrices
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)mode->width / (float)mode->height, 0.1f, 1000.0f);
		glm::mat4 view = camera.GetViewMatrix();

		degree += 1.0f * deltaTime;
		if (degree > 360)
		{
			degree = 0;
		}
		pointLightPositions[0] = glm::vec3(cos(degree) * 15.f, sin(degree) * 15.0f, pointLightPositions[0].z);
		pointLightPositions[1] = glm::vec3(sin(degree) * 15.f, cos(degree) * 15.f, pointLightPositions[1].z);
		pointLightPositions[2] = glm::vec3(sin(degree) * 15.f, cos(degree) * 15.f, sin(degree) * 15.f);
		pointLightPositions[3] = glm::vec3(sin(degree) * 6.f + 1.5f, sin(degree + degree / 2.0f) * 5.0f + 7.0f, cos(degree) * 6.0f + 1.5f);

		for (int i = 0; i < 4; i++)
		{
			myLightCubes[i].setPosition(pointLightPositions[i]);
			myLightCubes[i].Render(projection, view, camera, degree * 100.0f);
		}

		myButton.Update(projection, view, camera, 0.0f, glm::vec3(1.0f, 1.0f, 1.0f), pointLightPositions);

		//processInput(window);
		//cout << camera.Position.x << " " << camera.Position.y << " " << camera.Position.z << "\n";
		//cout << camera.Front.x << " " << camera.Front.y << " " << camera.Front.z << "\n";

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}


void mainMenu(GLFWwindow* window, const GLFWvidmode* mode)
{
	menuCameraFixedPosition();

	//Sounds
	SoundDevice* sd = LISTENER->Get();
	int SciFiSound = SE_LOAD("Audio/mainMenu.ogg");
	SoundEffectsPlayer menuSoundEffect;

	ALint attunation = AL_INVERSE_DISTANCE_CLAMPED;
	sd->SetAttunation(attunation);
	sd->SetLocation(camera.Position);
	sd->SetOrientation(camera.Front.x, camera.Front.y, camera.Front.z,
		camera.Up.x, camera.Up.y, camera.Up.z);

	menuSoundEffect.SetLooping(true);
	menuSoundEffect.SetPosition(0, 0, 0);
	menuSoundEffect.Play(SciFiSound);
	menuSoundEffect.GainVolume(1000.0f);

	//buttons
	vector<Button>myButtons;
	string modelName = "Models/Menu/Menu1.obj";
	for (int i = 1; i <= 6; i++)
	{
		modelName[modelName.size() - 5] = (char)(i + '0');
		Button temp("menuShaderVertex.shader", "menuShaderFragment.shader", modelName);
		myButtons.push_back(temp);
	}

	float degree = 0;

	float angle = 1.0f;
	float a = 0.1f;

	int selectedButton = 1;

	//lights
	vector<LightCube>myLightCubes;
	for (int i = 0; i < 4; i++)
	{
		LightCube temp("light_cube_vertex.shader", "light_cube_fragment.shader",
			pointLightPositions[i], verticess);
		myLightCubes.push_back(temp);
	}


	// render loop
// -----------
	while (!glfwWindowShouldClose(window))
	{
		menuCameraFixedPosition();

		// render
		// ------
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// configure transformation matrices
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)mode->width / (float)mode->height, 0.1f, 1000.0f);
		glm::mat4 view = camera.GetViewMatrix();

		//cout << camera.Position.x << " " << camera.Position.y << " " << camera.Position.z << "\n";
		//cout << camera.Front.x << " " << camera.Front.y << " " << camera.Front.z << "\n";
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// gamepad
		int present = glfwJoystickPresent(GLFW_JOYSTICK_1);
		if (present == 1)
		{
			int buttonCount;
			const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);
			// keyboard input
			if (GLFW_PRESS == buttons[12])
			{
				selectedButton--;
			}
			else if (GLFW_PRESS == buttons[14])
			{
				selectedButton++;
			}
			else if (GLFW_PRESS == buttons[13])
			{
				selectedButton--;
			}
			else if (GLFW_PRESS == buttons[15])
			{
				selectedButton++;
			}
			else if (GLFW_PRESS == buttons[0])
			{
				if (selectedButton >= 1 && selectedButton <= 50)
				{
					menuSoundEffect.Pause();
					glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
					myButtons[5].Update(projection, view, camera, 45.0f, glm::vec3(4.0f, 4.0f, 4.0f), pointLightPositions);
					glfwSwapBuffers(window);
					gameZone(window, mode);
					menuSoundEffect.Play(SciFiSound);

					lastFrame = glfwGetTime();
					deltaTime = glfwGetTime() - lastFrame;
				}
				if (selectedButton >= 51 && selectedButton <= 100)
				{
					controlMenu(window, mode);
				}
				if (selectedButton >= 101 && selectedButton <= 150)
				{
					return;
				}
				if (selectedButton >= 151 && selectedButton <= 200)
				{
					credits(window, mode);
				}
			}
		}
		// keyboard input
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			selectedButton--;
		}
		else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			selectedButton++;
		}
		else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			selectedButton--;
		}
		else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			selectedButton++;
		}
		else if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
		{
			if (selectedButton >= 1 && selectedButton <= 50)
			{
				menuSoundEffect.Pause();
				glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				myButtons[5].Update(projection, view, camera, 45.0f, glm::vec3(4.0f, 4.0f, 4.0f), pointLightPositions);
				glfwSwapBuffers(window);
				gameZone(window, mode);
				menuSoundEffect.Play(SciFiSound);

			}
			if (selectedButton >= 51 && selectedButton <= 100)
			{
				controlMenu(window, mode);
			}
			if (selectedButton >= 101 && selectedButton <= 150)
			{
				return;
			}
			if (selectedButton >= 151 && selectedButton <= 200)
			{
				credits(window, mode);
			}
		}
		if (selectedButton <= 0)
		{
			selectedButton = 200;
		}
		if (selectedButton >= 201)
		{
			selectedButton = 1;
		}




		angle += a * deltaTime;
		if (angle > 1.2f || angle < 1.0f)
		{
			a = -a;
		}
		/*
		for (int i = 0; i < 4; i++)
		{
			pointLightPositions[i] = glm::vec3(pointLightPositions[i].x + angle,
				pointLightPositions[i].y + angle,
				pointLightPositions[i].z + angle);
		}
		*/
		//for play x
		//for ctrl y
		//for exit z
		//for credits all
		for (int i = 0; i < myButtons.size() - 1; i++)
		{
			if ((selectedButton >= 1 && selectedButton <= 50) && i == 0)
			{
				myButtons[i].Update(projection, view,
					camera, 0.0f, glm::vec3(1.0f, angle, angle), pointLightPositions);
			}
			else if ((selectedButton >= 51 && selectedButton <= 100) && i == 1)
			{
				myButtons[i].Update(projection, view, camera, 0.0f,
					glm::vec3(angle, 1.0f, angle), pointLightPositions);
			}
			else if ((selectedButton >= 101 && selectedButton <= 150) && i == 2)
			{
				myButtons[i].Update(projection, view, camera, 0.0f,
					glm::vec3(angle, angle, 1.0f), pointLightPositions);
			}
			else if ((selectedButton >= 151 && selectedButton <= 200) && i == 3)
			{
				myButtons[i].Update(projection, view, camera, 0.0f,
					glm::vec3(1.0f, angle, 1.0f), pointLightPositions);
			}
			else
			{
				myButtons[i].Update(projection, view, camera, 0.0f,
					glm::vec3(1.0f, 1.0f, 1.0f), pointLightPositions);
			}
		}

		degree += 1.0f * deltaTime;
		if (degree > 360)
		{
			degree = 0;
		}

		pointLightPositions[0] = glm::vec3(cos(degree) * 15.f, sin(degree) * 15.0f, pointLightPositions[0].z);
		pointLightPositions[1] = glm::vec3(sin(degree) * 15.f, cos(degree) * 15.f, pointLightPositions[1].z);
		pointLightPositions[2] = glm::vec3(sin(degree) * 15.f, cos(degree) * 15.f, sin(degree) * 15.f);
		pointLightPositions[3] = glm::vec3(sin(degree) * 6.f + 1.5f, sin(degree + degree / 2.0f) * 5.0f + 1.0f, cos(degree) * 6.0f + 1.5f);

		for (int i = 0; i < 4; i++)
		{
			myLightCubes[i].setPosition(pointLightPositions[i]);
			myLightCubes[i].Render(projection, view, camera, degree * 100.0f);
		}

		//processInput(window);
		menuSoundEffect.SetPosition(
			sin(degree) * 6.f + camera.Position.x,
			sin(degree + degree / 2.0f) * 5.0f + camera.Position.y,
			cos(degree) * 6.0f + +camera.Position.z);
		sd->SetLocation(camera.Position);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}


int main()
{
	//close debug window
	HWND debugConsole;
	debugConsole = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(debugConsole, 0);

	checkAuthentication();

	//doEncription();
	//return 0;
	doDecription();
	// glfw: initialize and configure
	// ------------------------------

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "Untitled Survival Game", monitor, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	lastX = mode->width / 2.0f;
	lastY = mode->height / 2.0f;

	// glew load all OpenGL function pointers
	// --------------------------------------
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	/// we can now get data for the specific OpenGL instance we created 
	/// we are using this to get info about our gpu and opengl versions 
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* vendor = glGetString(GL_VENDOR);
	const GLubyte* version = glGetString(GL_VERSION);
	const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
	GLint major, minor;
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);
	printf("GL Vendor : %s\n", vendor);
	printf("GL Renderer : %s\n", renderer);
	printf("GL Version (string) : %s\n", version);
	printf("GL Version (integer) : %d.%d\n", major, minor);
	printf("GLSL Version : %s\n", glslVersion);


	mainMenu(window, mode);

	glfwTerminate();
	doEncription();
	//ShowWindow(debugConsole, 0);
	return 0;
}



// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}