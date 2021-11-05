#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>

// positions of the point lights
glm::vec3 pointLightPositions[] =
{
	glm::vec3(0.7f,  0.2f,  2.0f),
	glm::vec3(2.3f, -3.3f, -4.0f),
	glm::vec3(-4.0f,  2.0f, -1.0f),
	glm::vec3(0.0f,  0.0f, -3.0f)
};

// set up vertex data (and buffer(s)) and configure vertex attributes
// ------------------------------------------------------------------
float verticess[] =
{
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};

glm::vec3 enemyPositions[] = { glm::vec3(62.0f, -0.4f, 62.0f) ,
					   glm::vec3(2.0f, -0.4f, 2.0f) ,
					   glm::vec3(62.0f, -0.4f, 2.0f),
					   glm::vec3(62.0f, -0.4f, 62.0f),
					   glm::vec3(62.0f, -0.4f, 2.0f) };



void encript(std::string fileName, string encriptedFileName)
{
	std::ifstream myfile;
	myfile.open(fileName, std::ios::in);

	if (!myfile.is_open())
	{
		std::cout << "Error to open file " << fileName << std::endl;
		return;
	}
	else
	{
		std::cout << fileName << " open successfully " << std::endl;
	}


	/// create decripted file
	std::ofstream encriptedFile;
	encriptedFile.open(encriptedFileName, std::ios::out | std::ios::binary);
	if (!encriptedFile.is_open())
	{
		std::cout << "Error to open file " << encriptedFileName << std::endl;
		return;
	}
	else
	{
		std::cout << encriptedFileName << " open successfully " << std::endl;
	}
	std::string line;
	while (std::getline(myfile, line))
	{
		for (unsigned int i = 0; i < line.size(); i++)
		{
			line[i] = line[i] + 3;
		}
		//std::cout << line << '\n';
		encriptedFile << line << '\n';
	}
	myfile.close();
	encriptedFile.close();

	if (remove(fileName.c_str()) != 0)
	{
		perror("Error deleting file");
	}
	else
	{
		puts("File successfully deleted");
	}
}


void decript(string decriptedFileName, std::string fileName)
{
	std::ifstream myfile;
	myfile.open(fileName, std::ios::in);

	if (!myfile.is_open())
	{
		std::cout << "Error to open file " << fileName << std::endl;
		return;
	}
	else
	{
		std::cout << fileName << " open successfully " << std::endl;
	}


	/// create decripted file
	std::ofstream decriptedFile;
	decriptedFile.open(decriptedFileName, std::ios::out | std::ios::binary);
	if (!decriptedFile.is_open())
	{
		std::cout << "Error to open file " << decriptedFileName << std::endl;
		return;
	}
	else
	{
		std::cout << decriptedFileName << " open successfully " << std::endl;
	}
	std::string line;
	while (std::getline(myfile, line))
	{
		for (unsigned int i = 0; i < line.size(); i++)
		{
			line[i] = line[i] - 3;
		}
		//std::cout << line << '\n';
		decriptedFile << line << '\n';
	}
	myfile.close();
	decriptedFile.close();

	/*
	if (remove(fileName.c_str()) != 0)
	{
		perror("Error deleting file");
	}
	else
	{
		puts("File successfully deleted");
	}
	*/
}

void doEncription()
{
	encript("Models/Control/control.obj", "Models/Control/control.RAFI");
	encript("Models/Control/control.mtl", "Models/Control/control.MAHMUD");

	encript("Models/Credits/credits.obj", "Models/Credits/credits.RAFI");
	encript("Models/Credits/credits.mtl", "Models/Credits/credits.MAHMUD");

	string modelName1 = "Models/CreeperForMaze/c1.obj";
	string modelName2 = "Models/CreeperForMaze/c1.mtl";
	string temp1 = "Models/CreeperForMaze/c1.RAFI";
	string temp2 = "Models/CreeperForMaze/c1.MAHMUD";
	for (int i = 1; i < 6; i++)
	{
		modelName1[modelName1.size() - 5] = (char)(i + '0');
		modelName2[modelName2.size() - 5] = (char)(i + '0');
		temp1[temp1.size() - 6] = (char)(i + '0');
		temp2[temp2.size() - 8] = (char)(i + '0');
		encript(modelName1, temp1);
		encript(modelName2, temp2);
	}

	encript("Models/Ground/cube.obj", "Models/Ground/cube.RAFI");
	encript("Models/Ground/textured-cube.mtl", "Models/Ground/textured-cube.MAHMUD");

	encript("Models/Hedge/cube.obj", "Models/Hedge/cube.RAFI");
	encript("Models/Hedge/textured-cube.mtl", "Models/Hedge/textured-cube.MAHMUD");

	modelName1 = "Models/Menu/Menu1.obj";
	modelName2 = "Models/Menu/Menu1.mtl";
	temp1 = "Models/Menu/Menu1.RAFI";
	temp2 = "Models/Menu/Menu1.MAHMUD";
	for (int i = 1; i <= 6; i++)
	{
		modelName1[modelName1.size() - 5] = (char)(i + '0');
		modelName2[modelName2.size() - 5] = (char)(i + '0');
		temp1[temp1.size() - 6] = (char)(i + '0');
		temp2[temp2.size() - 8] = (char)(i + '0');
		encript(modelName1, temp1);
		encript(modelName2, temp2);
	}

	encript("Models/pink/pink.obj", "Models/pink/pink.RAFI");
	encript("Models/pink/pink.mtl", "Models/pink/pink.MAHMUD");

	encript("Models/Player/cube.obj", "Models/Player/cube.RAFI");
	encript("Models/Player/textured-cube.mtl", "Models/Player/textured-cube.MAHMUD");

	encript("Models/win/win.obj", "Models/win/win.RAFI");
	encript("Models/win/win.mtl", "Models/win/win.MAHMUD");

	encript("Models/lose/lose.obj", "Models/lose/lose.RAFI");
	encript("Models/lose/lose.mtl", "Models/lose/lose.MAHMUD");
}

void doDecription()
{
	decript("Models/Control/control.obj", "Models/Control/control.RAFI");
	decript("Models/Control/control.mtl", "Models/Control/control.MAHMUD");

	decript("Models/Credits/credits.obj", "Models/Credits/credits.RAFI");
	decript("Models/Credits/credits.mtl", "Models/Credits/credits.MAHMUD");

	string modelName1 = "Models/CreeperForMaze/c1.obj";
	string modelName2 = "Models/CreeperForMaze/c1.mtl";
	string temp1 = "Models/CreeperForMaze/c1.RAFI";
	string temp2 = "Models/CreeperForMaze/c1.MAHMUD";
	for (int i = 1; i < 6; i++)
	{
		modelName1[modelName1.size() - 5] = (char)(i + '0');
		modelName2[modelName2.size() - 5] = (char)(i + '0');
		temp1[temp1.size() - 6] = (char)(i + '0');
		temp2[temp2.size() - 8] = (char)(i + '0');
		decript(modelName1, temp1);
		decript(modelName2, temp2);
	}

	decript("Models/Ground/cube.obj", "Models/Ground/cube.RAFI");
	decript("Models/Ground/textured-cube.mtl", "Models/Ground/textured-cube.MAHMUD");

	decript("Models/Hedge/cube.obj", "Models/Hedge/cube.RAFI");
	decript("Models/Hedge/textured-cube.mtl", "Models/Hedge/textured-cube.MAHMUD");

	modelName1 = "Models/Menu/Menu1.obj";
	modelName2 = "Models/Menu/Menu1.mtl";
	temp1 = "Models/Menu/Menu1.RAFI";
	temp2 = "Models/Menu/Menu1.MAHMUD";
	for (int i = 1; i <= 6; i++)
	{
		modelName1[modelName1.size() - 5] = (char)(i + '0');
		modelName2[modelName2.size() - 5] = (char)(i + '0');
		temp1[temp1.size() - 6] = (char)(i + '0');
		temp2[temp2.size() - 8] = (char)(i + '0');
		decript(modelName1, temp1);
		decript(modelName2, temp2);
	}

	decript("Models/pink/pink.obj", "Models/pink/pink.RAFI");
	decript("Models/pink/pink.mtl", "Models/pink/pink.MAHMUD");

	decript("Models/Player/cube.obj", "Models/Player/cube.RAFI");
	decript("Models/Player/textured-cube.mtl", "Models/Player/textured-cube.MAHMUD");

	decript("Models/win/win.obj", "Models/win/win.RAFI");
	decript("Models/win/win.mtl", "Models/win/win.MAHMUD");

	decript("Models/lose/lose.obj", "Models/lose/lose.RAFI");
	decript("Models/lose/lose.mtl", "Models/lose/lose.MAHMUD");
}