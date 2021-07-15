#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.h"
#include "shader.h"


#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;


class Model
{
public:
	// model data 
	vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
	vector<Mesh>  meshes;
	string directory;
	bool gammaCorrection;

	// constructor, expects a filepath to a 3D model.
	Model()
	{

	}
	Model(string const& path, bool gamma = false) : gammaCorrection(gamma)
	{
		loadModel(path);
	}

	void setModelLocation(string path);

	void Draw(Shader& shader);

private:

	void loadModel(string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);

	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
		string typeName);

	unsigned int TextureFromFile(const char* path, const string& directory, bool gamma);

};

#endif // !MODEL_H
