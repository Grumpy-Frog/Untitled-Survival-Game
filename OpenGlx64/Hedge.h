#ifndef HEDGE_H
#define HEDGE_H

#include <string>
#include <cmath>
#include <vector>
#include <random>
#include <utility>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <Windows.h>


#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


#include "Shader.h"
#include "model.h"
#include "Mesh.h"
#include "MazeGenerator.h"
#include "Camera.h"
#include "CubeCollider.h"
#include "TexGen.h"
#include "Light.h"
//#include "TextureGenerator.h"

using namespace std;

class Hedge : public Light
{
private:
	std::vector<glm::mat4> modelMatricesHedge;
	std::vector<glm::mat4> modelMatricesGround;
	std::vector<CubeCollider> cubeColliders;

	Shader* cubeShader;
	Model* Hedges;
	Model* Ground;

	int* myMazeArray;

private:
	bool isIndexValid(int i, int j);

	void PositioningModels(int myMazeArray[], std::vector<glm::mat4>& modelMatricesRef);

	void PositioningModelsG(int myMazeArray[], std::vector<glm::mat4>& modelMatricesRef);

	void PositioningColliders(int myMazeArray[], std::vector<CubeCollider>& cubeCollidersRef);

public:
	std::vector<CubeCollider> getColliders() const;

	int* getMazeArray() const;

public:
	Hedge(const char* vertexShader, const char* fragmentShader, string hedgeModel, string groundModel);

	~Hedge();

	void update(glm::mat4& projection, glm::mat4& view, Camera& camera, glm::vec3* pointLights);

	void updateRender(glm::mat4& projection, glm::mat4& view, std::vector<glm::mat4>& modelMatricesRef, Model& modelRef);

	void init(glm::vec3* enmPos);

	void instance(std::vector<glm::mat4>& modelMatricesRef, Model& modelRef);
};

#endif //HEDGE_H
