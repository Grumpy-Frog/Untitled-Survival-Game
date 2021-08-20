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


#include <iostream>
#include <conio.h>

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
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

unsigned int loadTexture(char const* path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_MIRRORED_REPEAT : GL_REPEAT); // for this tutorial: use GL_CLAMP_TO_EDGE to prevent semi-transparent borders. Due to interpolation it takes texels from next repeat 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_MIRRORED_REPEAT : GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

int main()
{
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
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Untitled Survival Game", monitor, NULL);
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


	// build and compile shaders
	// -------------------------
	// load models
	// -----------
	// Hedge
	Hedge myHedges("lightInstanceVertex.shader", "lightInstanceFragment.shader", "Models/Hedge/cube.obj", "Models/Ground/cube.obj");
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
		myMazeArray);


	vector<Enemy>myEnemies;
	glm::vec3 x[3] = { glm::vec3(62.0f, 0.0f, 62.0f) ,
					   glm::vec3(2.0f, 0.0f, 62.0f) ,
					   glm::vec3(62.0f, 0.0f, 2.0f) };
	for (int i = 0; i < 3; i++)
	{
		Enemy  myEnemy1("modelVertex.shader", "modelFragment.shader", "Models/Player/cube.obj",
			x[i], 1, &deltaTime,
			&myPlayer, myMazeArray);
		myEnemies.push_back(myEnemy1);
	}




	// Input System
	InputProcess myinputProcess;


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

	/// <summary>
	/// Shadow//////////////////////////////
	/// </summary>
	/// <returns></returns>
	// configure depth map FBO
	// -----------------------
	//Shader simpleDepthShader("3.1.3.shadow_mapping_depthVS.shader", "3.1.3.shadow_mapping_depthFS.shader");
	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
	unsigned int depthMapFBO;
	glGenFramebuffers(1, &depthMapFBO);
	// create depth texture
	unsigned int depthMap;
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	// attach depth texture as FBO's depth buffer
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	///////////////////////////////////////////////////////////////////////////

	bool debug_mode = 1;


	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// render
		// ------
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// configure transformation matrices
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
		glm::mat4 view = camera.GetViewMatrix();



		if (debug_mode)
		{
			//camera = camera2;
			projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
			view = camera.GetViewMatrix();
			myHedges.update(projection, view, camera);
			myPlayer.Render(projection, view, camera);
			myPlayer.processInput(window);
			myPlayer.Update();

			for (int i = 0; i < 3; i++)
			{
				myEnemies[i].Render(projection, view, camera);
				myEnemies[i].Update();
			}


			if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
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
			camera.Position.x = 28.8f;
			camera.Position.y = 88.0f;
			camera.Position.z = 36.0f;
			camera.Front.x = 0.0174524f;
			camera.Front.y = -0.999848f;
			camera.Front.z = 7.71616e-11f;
			processInput(window);

		}
		else
		{
			/// <summary>
			/// temp
			/// </summary>
			/// <returns></returns>
			if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
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
			for (auto it : myEnemies)
			{
				it.Render(projection, view, camera);
				it.Update();
			}
			/// <summary>
			/// temp
			/// </summary>
			/// <returns></returns>
			projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
			view = camera.GetViewMatrix();
			myHedges.update(projection, view, camera);
			myPlayer.Update();

			// input
			// -----
			int present = glfwJoystickPresent(GLFW_JOYSTICK_1);
			if (present == 1)
			{
				myinputProcess.processInputGamePad(window, camera, myPlayer, myHedges, deltaTime);
			}
			myinputProcess.processInputKeyboard(window, camera, myPlayer, myHedges, deltaTime);
		}


		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
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