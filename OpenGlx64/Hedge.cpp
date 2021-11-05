#include "Hedge.h"


bool Hedge::isIndexValid(int i, int j)
{
	if (i<0 || j<0 || i>COL - 1 || j > COL - 1)
	{
		return false;
	}
	return true;
}

void Hedge::PositioningModels(int myMazeArray[], std::vector<glm::mat4>& modelMatricesRef)
{
	for (unsigned int i = 0; i < COL; i++)
	{
		for (unsigned int j = 0; j < COL; j++)
		{
			float x, y = 1.0, z;
			x = (i * COL + j) % COL * 2.0;
			z = (i * COL + j) / COL * 2.0;

			/*if (myMazeArray[i * COL + j] == 0)
			{
				cout << x << " " << z << "\n";
			}*/
			if (myMazeArray[i * COL + j] == 1)
			{
				while (y >= 0)
				{
					glm::mat4 model = glm::mat4(1.0f);
					model = glm::scale(model, glm::vec3(1.0f));
					model = glm::translate(model, glm::vec3(x, y, z));

					modelMatricesRef.push_back(model);


					int indexY[] = { i - 1,i + 1,i,i };
					int indexX[] = { j,j,j - 1,j + 1 };
					glm::vec3 extraHedgePositions[] =
					{
						glm::vec3(x, y,z - 1.0),
						glm::vec3(x,  y,z + 1.0),
						glm::vec3(x - 1.0, y, z),
						glm::vec3(x + 1.0, y, z)
					};

					for (unsigned int valueOfCheckingIndex = 0; valueOfCheckingIndex < 4; valueOfCheckingIndex++)
					{
						if (isIndexValid(indexY[valueOfCheckingIndex], indexX[valueOfCheckingIndex]))
						{
							if (myMazeArray[indexY[valueOfCheckingIndex] * COL + indexX[valueOfCheckingIndex]] == 1)
							{
								model = glm::mat4(1.0f);
								model = glm::scale(model, glm::vec3(1.0f));
								model = glm::translate(model, extraHedgePositions[valueOfCheckingIndex]);

								modelMatricesRef.push_back(model);
							}
						}
					}
					y--;
				}
			}
		}
	}
}

void Hedge::PositioningModelsG(int myMazeArray[], std::vector<glm::mat4>& modelMatricesRef)
{
	for (unsigned int i = 0; i < COL; i++)
	{
		for (unsigned int j = 0; j < COL; j++)
		{
			float x, y = -1.0, z;
			x = (i * COL + j) % COL * 2.0;
			z = (i * COL + j) / COL * 2.0;

			if (myMazeArray[i * COL + j] == 0)
			{
				//while (y >= 0)
				{
					glm::mat4 model = glm::mat4(1.0f);
					model = glm::scale(model, glm::vec3(1.0f));
					model = glm::translate(model, glm::vec3(x, y, z));

					modelMatricesRef.push_back(model);


					glm::vec3 extraHedgePositions[] =
					{
						glm::vec3(x, y,z - 1.0),
						glm::vec3(x,  y,z + 1.0),
						glm::vec3(x - 1.0, y, z),
						glm::vec3(x + 1.0, y, z),

						glm::vec3(x + 1.0, y, z + 1.0),
						glm::vec3(x + 1.0, y, z - 1.0),
						glm::vec3(x - 1.0, y, z + 1.0),
						glm::vec3(x - 1.0, y, z - 1.0)
					};

					for (unsigned int valueOfCheckingIndex = 0; valueOfCheckingIndex < 8; valueOfCheckingIndex++)
					{

						model = glm::mat4(1.0f);
						model = glm::scale(model, glm::vec3(1.0f));
						model = glm::translate(model, extraHedgePositions[valueOfCheckingIndex]);

						modelMatricesRef.push_back(model);

					}
				}
			}
		}
	}
}

void Hedge::PositioningColliders(int myMazeArray[], std::vector<CubeCollider>& cubeCollidersRef)
{
	for (unsigned int i = 0; i < COL; i++)
	{
		for (unsigned int j = 0; j < COL; j++)
		{
			float x, y = 1.0, z;
			x = (i * COL + j) % COL * 2.0;
			z = (i * COL + j) / COL * 2.0;

			if (myMazeArray[i * COL + j] == 1)
			{
				while (y >= 0)
				{
					glm::vec3 pos = glm::vec3(x, y, z);
					CubeCollider collider2(pos);

					cubeCollidersRef.push_back(collider2);

					int indexY[] = { i - 1,i + 1,i,i };
					int indexX[] = { j,j,j - 1,j + 1 };
					glm::vec3 extraHedgePositions[] =
					{
						glm::vec3(x, y,z - 1.0),
						glm::vec3(x,  y,z + 1.0),
						glm::vec3(x - 1.0, y, z),
						glm::vec3(x + 1.0, y, z)
					};

					for (unsigned int valueOfCheckingIndex = 0; valueOfCheckingIndex < 4; valueOfCheckingIndex++)
					{
						if (isIndexValid(indexY[valueOfCheckingIndex], indexX[valueOfCheckingIndex]))
						{
							if (myMazeArray[indexY[valueOfCheckingIndex] * COL + indexX[valueOfCheckingIndex]] == 1)
							{
								CubeCollider collider(extraHedgePositions[valueOfCheckingIndex]);

								cubeCollidersRef.push_back(collider);
							}
						}
					}
					y--;
				}
			}
		}
	}
}


std::vector<CubeCollider> Hedge::getColliders() const
{
	return this->cubeColliders;
}

int* Hedge::getMazeArray() const
{
	return this->myMazeArray;
}

Hedge::Hedge(const char* vertexShader, const char* fragmentShader, string hedgeModel, string groundModel)
{
	modelMatricesHedge.clear();
	modelMatricesGround.clear();
	cubeColliders.clear();

	this->cubeShader = new Shader(vertexShader, fragmentShader);

	/// Generate Texture for hedge and ground
	TexGen textureGenerator;
	textureGenerator.del();
	auto ground = textureGenerator.ground();
	textureGenerator.actual_visualization_function(ground, false);

	auto hedge = textureGenerator.hedge();
	textureGenerator.actual_visualization_function(hedge, true);
	system("start hedge.exe");
	system("start ground.exe");

	//loading
	float time = 55.0f;
	while (time > 0.0f)
	{
		time -= 1.0f;
		system("cls");
	}

	this->Hedges = new Model(hedgeModel);
	this->Ground = new Model(groundModel);

}

Hedge::~Hedge()
{
	cout << "Hedge destroyed\n";
	delete this->cubeShader;
	delete this->Hedges;
	delete this->Ground;
	modelMatricesHedge.clear();
	modelMatricesGround.clear();
	cubeColliders.clear();
	delete this->myMazeArray;
}

void Hedge::update(glm::mat4& projection, glm::mat4& view, Camera& camera, glm::vec3* pointLights)
{
	this->UpdateLighting(projection, view, camera, *this->cubeShader, pointLights);

	updateRender(projection, view, modelMatricesHedge, *Hedges);
	updateRender(projection, view, modelMatricesGround, *Ground);
}

void Hedge::updateRender(glm::mat4& projection, glm::mat4& view, std::vector<glm::mat4>& modelMatricesRef, Model& modelRef)
{
	this->cubeShader->use();
	this->cubeShader->setMat4("projection", projection);
	this->cubeShader->setMat4("view", view);

	//shadow
	this->cubeShader->setInt("shadowMap", 1);

	// draw modelRef
	this->cubeShader->use();
	this->cubeShader->setInt("texture_diffuse1", 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, modelRef.textures_loaded[0].id); // note: we also made the textures_loaded vector public (instead of private) from the model class.
	for (unsigned int i = 0; i < modelRef.meshes.size(); i++)
	{
		glBindVertexArray(modelRef.meshes[i].VAO);
		glDrawElementsInstanced(GL_TRIANGLES, modelRef.meshes[i].indices.size(), GL_UNSIGNED_INT, 0, modelMatricesRef.size());
		glBindVertexArray(0);
	}
}

void Hedge::init(glm::vec3* enmPos)
{
	Maze myMazeObj;
	myMazeObj.generateMaze();
	myMazeObj.manipulate(enmPos);
	int* temp = myMazeObj.getMaze();
	myMazeArray = new int[COL * COL];
	for (unsigned int i = 0; i < COL; i++)
	{
		for (unsigned int j = 0; j < COL; j++)
		{
			myMazeArray[i * COL + j] = temp[i * COL + j];
		}
	}

	//MazeRenderFunctions::
	PositioningModels(myMazeArray, modelMatricesHedge);
	PositioningModelsG(myMazeArray, modelMatricesGround);
	PositioningColliders(myMazeArray, cubeColliders);

	// configure instanced array
	// -------------------------
	instance(modelMatricesHedge, *Hedges);
	instance(modelMatricesGround, *Ground);
}

void Hedge::instance(std::vector<glm::mat4>& modelMatricesRef, Model& modelRef)
{
	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, modelMatricesRef.size() * sizeof(glm::mat4), &modelMatricesRef[0], GL_STATIC_DRAW);


	// set transformation matrices as an instance vertex attribute (with divisor 1)
	// note: we're cheating a little by taking the, now publicly declared, VAO of the model's mesh(es) and adding new vertexAttribPointers
	// normally you'd want to do this in a more organized fashion, but for learning purposes this will do.
	// -----------------------------------------------------------------------------------------------------------------------------------
	for (unsigned int i = 0; i < modelRef.meshes.size(); i++)
	{
		unsigned int VAO = modelRef.meshes[i].VAO;
		glBindVertexArray(VAO);
		// set attribute pointers for matrix (4 times vec4)
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
		glEnableVertexAttribArray(6);
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);
		glVertexAttribDivisor(5, 1);
		glVertexAttribDivisor(6, 1);

		glBindVertexArray(0);
	}
}