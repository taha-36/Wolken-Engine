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
#include <glm/gtc/type_ptr.hpp>

class Shader {
public :
	unsigned int id;

	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);

	void Activate();

	// Utility functions
	std::string loadShaderSrc(const char* filepath);
	GLuint compileShader(const char* filepath, GLenum type);

	//uniform functions
	void setMat4(const std::string& name, glm::mat4 val);
	void setInt(const std::string& name, int value);
	void setBool(const std::string& name, bool value);
};