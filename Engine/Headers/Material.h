#pragma once
#include <fstream>
#include <filesystem>
#include <iostream>
#include "Shader.h"
#include "Texture.h"
#include "Component.h"
#include "nlohmann/json.hpp"
class Material : public Component
{
public:
	std::string materialPath;
	glm::vec3 mainColor;
	std::string name;
	Shader* shader;
	Texture* texture;

	Material(std::string material_path);
	nlohmann::json Serialize() const;
	static void Deserialize(std::string path);
};