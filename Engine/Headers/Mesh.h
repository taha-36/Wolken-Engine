#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <KHR/khrplatform.h>
#include "Shader.h"
#include <vector>
#include "Material.h"

class Mesh
{
public:
	std::vector<float> vertsPoses;
	std::vector<float> vertsColors;
	std::vector<unsigned int> indices;

	int vertCount;
	int indexCount;

	unsigned int VAO;
	unsigned int posesVBO;
	unsigned int colorsVBO;
	unsigned int EBO;

	bool useVertsColors;

	Material* material;

	Mesh(std::vector<float> vertsPoses, std::vector<unsigned int> indicies, std::vector<float> vertsColours);
	Mesh(std::vector<float> vertsPoses, std::vector<unsigned int> indicies);
	~Mesh();

	void ActivateMesh();
	void ActivateMeshColorless();
	void Render();
};
