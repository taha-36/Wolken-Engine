#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <KHR/khrplatform.h>
#include <fstream>
#include <iostream>
#include "nlohmann/json.hpp"
class Texture
{
public:
	unsigned int texId;
	std::string path;
	Texture(const char* texturePath);

	nlohmann::json Serialize() const;
	static Texture Deserialize(const nlohmann::json& j);
};