#ifndef LIGHTCUBE_H
#define LIGHTCUBE_H


#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "shader.h"
#include "Camera.h"

class LightCube
{
private:
	Shader* lightCubeShader;

	glm::vec3 scale;
	glm::vec3 position;
	float* vertices;
	unsigned int VBO, cubeVAO;
	unsigned int lightCubeVAO;
public:
	LightCube(const char* vertexShader, const char* fragmentShader,
		glm::vec3 pos, float* vert,
		glm::vec3 newScale = glm::vec3(1.0f, 1.0f, 1.0f))
	{
		this->lightCubeShader = new Shader(vertexShader, fragmentShader);
		this->scale = newScale;
		this->position = pos;
		this->vertices = vert;

		//for (int i = 0; i < 288; i++)
		//{
		//	cout << vertices[i] << " ";
		//}

		this->initBuffer();
	}

	~LightCube()
	{
		//delete this->lightCubeShader;
	}

	void initBuffer()
	{
		// first, configure the cube's VAO (and VBO)

		glGenVertexArrays(1, &cubeVAO);
		glGenBuffers(1, &VBO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 288, vertices, GL_STATIC_DRAW);

		glBindVertexArray(cubeVAO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		// second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)

		glGenVertexArrays(1, &lightCubeVAO);
		glBindVertexArray(lightCubeVAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		// note that we update the lamp's position attribute's stride to reflect the updated buffer data
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}

	void Render(glm::mat4& projection, glm::mat4& view, Camera& camera,
		float angle,
		glm::vec3 newScale = glm::vec3(1.0f, 1.0f, 1.0f))
	{
		lightCubeShader->use();
		lightCubeShader->setMat4("projection", projection);
		lightCubeShader->setMat4("view", view);
		// we now draw as many light bulbs as we have point lights.
		glBindVertexArray(lightCubeVAO);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, this->position);
		model = glm::scale(model, this->scale); 
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.0f, 0.5f));
		lightCubeShader->setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);

	}

	glm::vec3 getPosition() const
	{
		return this->position;
	}

	void setPosition(glm::vec3 newPos)
	{
		this->position = newPos;
	}

	glm::vec3 getScale() const
	{
		return this->scale;
	}

	void setScale(glm::vec3 newScale)
	{
		this->scale = newScale;
	}
};

#endif // !LIGHTCUBE_H
