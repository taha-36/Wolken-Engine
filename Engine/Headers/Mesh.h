#pragma once
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <glm/glm.hpp>
//#include <KHR/khrplatform.h>
#include <vector>

class Mesh
{
public:
	std::vector<float> vertsPoses;
	std::vector<float> vertsColors;
	std::vector<float> uv;
	std::vector<unsigned int> indices;

	int vertCount;
	int indexCount;

	bool useVertsColors;

	Mesh(std::vector<float> vertsPoses, std::vector<unsigned int> indicies, std::vector<float> vertsColours);
	Mesh(std::vector<float> vertsPoses, std::vector<unsigned int> indicies);
};
