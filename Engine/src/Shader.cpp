#include "Shader.h"

Shader::Shader(std::string shader_path, std::string vertexShaderPath, std::string fragmentShaderPath)
{
	int success;
	char infoLog[512];

	GLuint vertexShader = compileShader(vertexShaderPath, GL_VERTEX_SHADER);
	GLuint fragShader = compileShader(fragmentShaderPath, GL_FRAGMENT_SHADER);

	id = glCreateProgram();
	glAttachShader(id, vertexShader);
	glAttachShader(id, fragShader);
	glLinkProgram(id);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "Error with vertex shader com: " << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);

	this->shaderPath = shader_path;
	this->vertexShaderPath = vertexShaderPath;
	this->fragmentShaderPath = fragmentShaderPath;
	std::filesystem::path p = shader_path;
	this->name = p.stem().string();

	AssetsHandler::Instance().SHADERS.insert({ this->shaderPath, this });
}

void Shader::Activate()
{
	glUseProgram(id);
}

void Shader::setInt(const std::string& name, int value) {
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}
void Shader::setUInt(const std::string& name, int value) {
	glUniform1ui(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setBool(const std::string& name, bool value)
{
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}
void Shader::setFloat(const std::string& name, float value)
{
	glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}
void Shader::setVec4(const std::string& name, glm::vec4 vec)
{
	glUniform4f(glGetUniformLocation(id, name.c_str()), vec.x, vec.y, vec.z, vec.w);
}

void Shader::setVec3(const std::string& name, glm::vec3 vec)
{
	glUniform3f(glGetUniformLocation(id, name.c_str()), vec.x, vec.y, vec.z);
}
std::string Shader::loadShaderSrc(std::string filename)
{
	std::ifstream file;
	std::stringstream buf;

	std::string ret = "";

	file.open(filename);

	if (file.is_open())
	{
		buf << file.rdbuf();
		ret = buf.str();
	}
	else
	{
		std::cout << "Couldn't open " << filename << std::endl;
	}
	file.close();

	return ret;
}

GLuint Shader::compileShader(std::string filePath, GLenum type)
{
	int success;
	char infoLog[512];

	GLuint ret = glCreateShader(type);
	std::string shaderSrc = loadShaderSrc(filePath);
	const GLchar* shader = shaderSrc.c_str();
	glShaderSource(ret, 1, &shader, NULL);
	glCompileShader(ret);

	glGetShaderiv(ret, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(ret, 512, NULL, infoLog);
		std::cout << "Error with frag shader com: " << infoLog << std::endl;
	}

	return ret;
}

void Shader::setMat4(const std::string& name, glm::mat4 val)
{
	glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(val));
}

nlohmann::json Shader::Serialize() const
{
	nlohmann::json j = {
		{"Name", name},
		{"ShaderPath", shaderPath},
		{"VertexPath", vertexShaderPath},
		{"FragmentPath", fragmentShaderPath}
	};

	std::string path = this->shaderPath;
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
	if (!data.contains("Shaders")) {
		data["Shaders"] = nlohmann::json::array();
	}

	// Check for duplicates
	auto& materials = data["Shaders"];
	bool exists = std::find(materials.begin(), materials.end(), shaderPath) != materials.end();
	if (!exists)
	{
		AssetsHandler::Instance().ASSETSJSON["Shaders"].push_back(shaderPath);
		AssetsHandler::Instance().SaveJson();
	}
	return j;
}

void Shader::Deserialize(std::string path)
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

	if (!data.contains("Shaders"))
		return;

	if (std::filesystem::exists(path))
	{
		std::ifstream shaderFile(path);
		nlohmann::json shaderJ;
		if (shaderFile.is_open())
		{
			shaderFile >> shaderJ;
		}

		std::string shaderPath = shaderJ["Material Path"];
		std::string vertPath = shaderJ["VertexPath"];
		std::string fragPath = shaderJ["FragmentPath"];
		Shader* shader = new Shader(shaderPath, vertPath, fragPath);
		shader->name = shaderJ["Name"];
	}
}