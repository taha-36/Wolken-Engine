#include "Material.h"
#include "Globals.h"
#include "AssetsHandler.h"

Material::Material(std::string material_path)
{
	this->shader = Globals::Instance().defaultShader;
	this->texture = nullptr;
	this->materialPath = material_path;
	this->mainColor = glm::vec3(1.0);
	std::filesystem::path p = material_path;
	this->name = p.stem().string();
	AssetsHandler::Instance().MATERIALS.insert({this->materialPath, this});
}
nlohmann::json Material::Serialize() const
{
	nlohmann::json j = {
		{"Name", name},
		{ "Material Path", materialPath },
		{ "Main Color", {mainColor.x, mainColor.y, mainColor.z} },
		{ "Shader Path", shader ? shader->shaderPath : nullptr }
	};

	std::string path = this->materialPath;
	std::filesystem::path filePath(path);
	std::filesystem::path dirPath = filePath.parent_path();


	// Ensure the directory exists
	if (!std::filesystem::exists(dirPath))
	{
		std::filesystem::create_directories(dirPath);
	}

	std::ofstream file(path);
	if (file.is_open())
	{
		file << j.dump(4);
		file.close();
		std::cout << "done" << std::endl;
	}
	else
	{
		std::cerr << "Failed to open file" << "\n";
	}
	nlohmann::json data;

	// Read existing data (if file exists)
	std::ifstream inFile("core/assets.json");
	if (inFile.is_open()) {
		inFile >> data;
		inFile.close();
	}

	// Initialize "Materials" array if it doesn't exist
	if (!data.contains("Materials")) {
		data["Materials"] = nlohmann::json::array();
	}

	// Check for duplicates
	auto& materials = data["Materials"];
	bool exists = std::find(materials.begin(), materials.end(), materialPath) != materials.end();
	if (!exists)
	{
		AssetsHandler::Instance().ASSETSJSON["Materials"].push_back(materialPath);
		AssetsHandler::Instance().SaveJson();
	}
	return j;
}

void Material::Deserialize(std::string path)
{
	if (!std::filesystem::exists("core/assets.json"))
		return;

	nlohmann::json data;
	std::ifstream file("core/assets.json");
	if (file.is_open())
	{
		file >> data;
		file.close();
	}

	if (!data.contains("Materials"))
		return;

	if (std::filesystem::exists(path))
	{
		std::ifstream matFile(path);
		nlohmann::json matJ;
		if (matFile.is_open())
		{
			matFile >> matJ;
		}

		std::string matPath = matJ["Material Path"];
		Material* mat = new Material(matPath);
		glm::vec3 mainColor;
		mainColor.x = matJ["Main Color"][0];
		mainColor.y = matJ["Main Color"][1];
		mainColor.z = matJ["Main Color"][2];
		mat->mainColor = mainColor;
		if (std::filesystem::exists(matJ["Shader Path"]) && AssetsHandler::Instance().SHADERS.contains(matJ["Shader Path"]))
		{
			Shader* shad = AssetsHandler::Instance().SHADERS[matJ["Shader Path"]];
			mat->shader = shad;
		}
	}
}