#include "Light.h"


Light::Light()
{
	this->ambient = 0.2f;
	this->counter = 1;
}

Light::~Light()
{

}


void Light::UpdateLighting(glm::mat4& projection, glm::mat4& view, Camera& camera, Shader& myShader,float &deltaTime,
	glm::vec3* pointLightPositions)
{
	updateAmbient(deltaTime);
	myShader.use();
	myShader.setMat4("projection", projection);
	myShader.setMat4("view", view);

	// be sure to activate shader when setting uniforms/drawing objects
	myShader.setVec3("viewPos", camera.Position);
	myShader.setFloat("material.shininess", 32.0f);


	// directional light
	myShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
	myShader.setVec3("dirLight.ambient", 0.1f, 0.1f, 0.1f);
	myShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f); // have to change
	myShader.setVec3("dirLight.specular", 0.65f, 0.65f, 0.65f);

	// point light 1
	myShader.setVec3("pointLights[0].position", pointLightPositions[0]);
	myShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
	myShader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
	myShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
	myShader.setFloat("pointLights[0].constant", 1.0f);
	myShader.setFloat("pointLights[0].linear", 0.09);
	myShader.setFloat("pointLights[0].quadratic", 0.032);
	// point light 2
	myShader.setVec3("pointLights[1].position", pointLightPositions[1]);
	myShader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
	myShader.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
	myShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
	myShader.setFloat("pointLights[1].constant", 1.0f);
	myShader.setFloat("pointLights[1].linear", 0.09);
	myShader.setFloat("pointLights[1].quadratic", 0.032);
	// point light 3
	myShader.setVec3("pointLights[2].position", pointLightPositions[2]);
	myShader.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
	myShader.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
	myShader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
	myShader.setFloat("pointLights[2].constant", 1.0f);
	myShader.setFloat("pointLights[2].linear", 0.09);
	myShader.setFloat("pointLights[2].quadratic", 0.032);
	// point light 4
	myShader.setVec3("pointLights[3].position", pointLightPositions[3]);
	myShader.setVec3("pointLights[3].ambient", glm::vec3(ambient));
	myShader.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
	myShader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
	myShader.setFloat("pointLights[3].constant", 1.0f);
	myShader.setFloat("pointLights[3].linear", 0.09);
	myShader.setFloat("pointLights[3].quadratic", 0.032);
	// spotLight
	myShader.setVec3("spotLight.position", glm::vec3(1000.0, 1000.0, 1000.0f));
	myShader.setVec3("spotLight.direction", camera.Front);
	myShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
	myShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
	myShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
	myShader.setFloat("spotLight.constant", 1.0f);
	myShader.setFloat("spotLight.linear", 0.09);
	myShader.setFloat("spotLight.quadratic", 0.032);
	myShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
	myShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
}


void Light::updateAmbient(float &deltaTime)
{
	
	if (this->ambient > 0.9f || this->ambient < 0.01f)
	{
		this->counter = this->counter * -1;
		if (this->ambient > 0.9f)
		{
			this->ambient = 0.89f;
		}
		else
		{
			this->ambient = 0.1f;
		}
	}
	else
	{
		this->ambient += (this->counter * deltaTime);
	}
	//std::cout << this->ambient << "\n";
}
