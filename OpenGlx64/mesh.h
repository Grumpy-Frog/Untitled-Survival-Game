#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm.hpp>

#include <string>
#include <vector>
#include <gtc\matrix_transform.hpp>

#include "Shader.h"
#include "Mesh.h"

using namespace std;

struct Vertex
{
	//position
	glm::vec3 Position;
	// normal
	glm::vec3 Normal;
	//texCoords
	glm::vec2 TexCoords;
	//tangent
	glm::vec3 Tangent;
	//bitangent
	glm::vec3 Bitangent;
};

struct Texture
{
	unsigned int id;
	string type;
	string path;
};

class Mesh
{
public:
	// mesh data
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;
	unsigned int VAO;

	//constructor
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);

	//render the mesh
	void Draw(Shader& shader);

private:
	// render data
	unsigned int VBO, EBO;

	// initializes all the buffer objects/arrays
	void setupMesh();

};

#endif //MESH_H
