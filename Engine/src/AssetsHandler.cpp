#include "AssetsHandler.h"
#include "Material.h"
#include "Shader.h"

AssetsHandler::AssetsHandler()
{
	std::string path = "core/Assets.json";
	std::filesystem::path filePath(path);
	std::filesystem::path dirPath = filePath.parent_path();

	if (!std::filesystem::exists(path))
	{
		if (!std::filesystem::exists(dirPath))
		{
			std::filesystem::create_directories(dirPath);
		}
		std::ofstream file(path);
		if (file.is_open())
		{
			file << ASSETSJSON.dump(4);
			file.close();
			std::cout << "done" << std::endl;
		}
		else
		{
			std::cerr << "Failed to open file" << "\n";
		}
	}
	else
	{
		std::ifstream file("core/Assets.json");
		if (file.is_open())
		{
			// Deserialize the JSON data into the 'j' object
			file >> ASSETSJSON;
			file.close();
		}
	}
	
}
void AssetsHandler::SaveJson()
{
	std::string path = "core/Assets.json";
	std::ofstream file(path);
	if (file.is_open())
	{
		file << ASSETSJSON.dump(4);
		file.close();
		std::cout << "done" << std::endl;
	}
	else
	{
		std::cerr << "Failed to open file" << "\n";
	}
}
void AssetsHandler::LoadAssets()
{
	for (std::string path : ASSETSJSON["Materials"])
	{
		Material::Deserialize(path);
	}

	for (std::string path : ASSETSJSON["Shaders"])
	{
		Shader::Deserialize(path);
	}
}