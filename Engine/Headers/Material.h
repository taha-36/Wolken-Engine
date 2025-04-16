#pragma once
#include"Shader.h"
#include"Texture.h"

class Material
{
public:
	Shader* shader;
	Material();
	Texture* texture;
};