#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <KHR/khrplatform.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>
#include <filesystem>
#include <glm/gtc/type_ptr.hpp>
#include "nlohmann/json.hpp"
#include "AssetsHandler.h"

class Shader {
public :
	unsigned int id;

	Shader(std::string shader_path, std::string vertexShaderPath, std::string fragmentShaderPath);

	std::string shaderPath;
	std::string vertexShaderPath;
	std::string fragmentShaderPath;
	std::string name;

	void Activate();

	// Utility functions
	std::string loadShaderSrc(std::string filepath);
	GLuint compileShader(std::string filepath, GLenum type);

	//uniform functions
	void setMat4(const std::string& name, glm::mat4 val);
	void setInt(const std::string& name, int value);
	void setBool(const std::string& name, bool value);
	void setFloat(const std::string& name, float value);
	void setUInt(const std::string& name, int value);
	void setVec4(const std::string& name, glm::vec4 vec);
	void setVec3(const std::string& name, glm::vec3 vec);

	nlohmann::json Serialize() const;
	static void Deserialize(std::string path);
};