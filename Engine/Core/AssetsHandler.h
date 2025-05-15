#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include "nlohmann/json.hpp"
class Shader;
class Material;
class AssetsHandler
{
public:
	std::unordered_map<std::string, Shader*> SHADERS;
	std::unordered_map<std::string, Material*> MATERIALS;
	nlohmann::json ASSETSJSON;
	static AssetsHandler& Instance()
	{
		static AssetsHandler instance;
		return instance;
	}
	AssetsHandler();
	void SaveJson();
	void LoadAssets();
};