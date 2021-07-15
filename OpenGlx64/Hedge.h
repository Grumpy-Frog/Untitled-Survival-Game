#ifndef HEDGE_H
#define HEDGE_H

#include <string>
#include <vector>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "Shader.h"
#include "model.h"
#include "Mesh.h"
#include "MazeGenerator.h"
#include "Camera.h"
using namespace std;


class Hedge
{
private:
	std::vector<glm::mat4> modelMatrices;

	bool isIndexValid(int i, int j)
	{
		if (i<0 || j<0 || i>COL - 1 || j > COL - 1)
		{
			return false;
		}
		return true;
	}

	void PositioningModels(int myMazeArray[], std::vector<glm::mat4>& modelMatrices)
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
						glm::mat4 model = glm::mat4(1.0f);
						model = glm::scale(model, glm::vec3(1.0f));
						model = glm::translate(model, glm::vec3(x, y, z));

						modelMatrices.push_back(model);

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


									modelMatrices.push_back(model);
								}
							}
						}
						y--;
					}
				}
			}
		}
	}
public:
	Hedge(Model &cube)
	{
		modelMatrices.clear();
		init(cube);
	}

	void update(glm::mat4& projection, glm::mat4& view,Shader &cubeShader,Model &cube,Camera &camera)
	{
		// positions of the point lights
		glm::vec3 pointLightPositions[] =
		{
			glm::vec3(0.7f,  0.2f,  2.0f),
			glm::vec3(2.3f, -3.3f, -4.0f),
			glm::vec3(-4.0f,  2.0f, -12.0f),
			glm::vec3(0.0f,  0.0f, -3.0f)
		};

		// be sure to activate shader when setting uniforms/drawing objects
		cubeShader.use();
		//myShader.setVec3("light.direction", -1.0f, -1.0f, -1.0f);
		cubeShader.setVec3("viewPos", camera.Position);
		cubeShader.setVec3("light.position", camera.Position);

		// directional light
		cubeShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
		cubeShader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
		cubeShader.setVec3("dirLight.diffuse", 1.0f, 1.0f, 1.0f);
		cubeShader.setVec3("dirLight.specular", 1.5f, 1.5f, 1.5f);

		// point light 1
		cubeShader.setVec3("pointLights[0].position", pointLightPositions[0]);
		cubeShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
		cubeShader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
		cubeShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
		cubeShader.setFloat("pointLights[0].constant", 1.0f);
		cubeShader.setFloat("pointLights[0].linear", 0.09);
		cubeShader.setFloat("pointLights[0].quadratic", 0.032);
		// point light 2
		cubeShader.setVec3("pointLights[1].position", pointLightPositions[1]);
		cubeShader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
		cubeShader.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
		cubeShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
		cubeShader.setFloat("pointLights[1].constant", 1.0f);
		cubeShader.setFloat("pointLights[1].linear", 0.09);
		cubeShader.setFloat("pointLights[1].quadratic", 0.032);
		// point light 3
		cubeShader.setVec3("pointLights[2].position", pointLightPositions[2]);
		cubeShader.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
		cubeShader.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
		cubeShader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
		cubeShader.setFloat("pointLights[2].constant", 1.0f);
		cubeShader.setFloat("pointLights[2].linear", 0.09);
		cubeShader.setFloat("pointLights[2].quadratic", 0.032);
		// point light 4
		cubeShader.setVec3("pointLights[3].position", pointLightPositions[3]);
		cubeShader.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
		cubeShader.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
		cubeShader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
		cubeShader.setFloat("pointLights[3].constant", 1.0f);
		cubeShader.setFloat("pointLights[3].linear", 0.09);
		cubeShader.setFloat("pointLights[3].quadratic", 0.032);

		// spotLight
		cubeShader.setVec3("spotLight.position", camera.Position);
		cubeShader.setVec3("spotLight.direction", camera.Front);
		cubeShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
		cubeShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
		cubeShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
		cubeShader.setFloat("spotLight.constant", 1.0f);
		cubeShader.setFloat("spotLight.linear", 0.09);
		cubeShader.setFloat("spotLight.quadratic", 0.032);
		cubeShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(10.0f)));
		cubeShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

		cubeShader.setInt("material.diffuse", 0);
		cubeShader.setInt("material.specular", 1);
		cubeShader.setInt("material.emission", 2);
		cubeShader.setFloat("material.shininess", 64.0f);

		updateRender(projection, view, cubeShader, cube);
	}

	void updateRender(glm::mat4& projection, glm::mat4& view,Shader &cubeShader, Model &cube)
	{
		cubeShader.use();
		cubeShader.setMat4("projection", projection);
		cubeShader.setMat4("view", view);


		// draw cube
		cubeShader.use();
		cubeShader.setInt("texture_diffuse1", 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, cube.textures_loaded[0].id); // note: we also made the textures_loaded vector public (instead of private) from the model class.
		for (unsigned int i = 0; i < cube.meshes.size(); i++)
		{
			glBindVertexArray(cube.meshes[i].VAO);
			glDrawElementsInstanced(GL_TRIANGLES, cube.meshes[i].indices.size(), GL_UNSIGNED_INT, 0, modelMatrices.size());
			glBindVertexArray(0);
		}
	}

	void init(Model &cube)
	{
		Maze myMazeObj;
		myMazeObj.generateMaze();
		int* myMazeArray = myMazeObj.getMaze();
		//MazeRenderFunctions::
		PositioningModels(myMazeArray, modelMatrices);

		// configure instanced array
	// -------------------------
		unsigned int buffer;
		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, modelMatrices.size() * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);


		// set transformation matrices as an instance vertex attribute (with divisor 1)
		// note: we're cheating a little by taking the, now publicly declared, VAO of the model's mesh(es) and adding new vertexAttribPointers
		// normally you'd want to do this in a more organized fashion, but for learning purposes this will do.
		// -----------------------------------------------------------------------------------------------------------------------------------
		for (unsigned int i = 0; i < cube.meshes.size(); i++)
		{
			unsigned int VAO = cube.meshes[i].VAO;
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

};

#endif //HEDGE_H
