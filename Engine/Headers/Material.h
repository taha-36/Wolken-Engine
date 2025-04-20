#pragma once
#include"Shader.h"
#include"Texture.h"
#include "Component.h"

class Material : public Component
{
public:
	Shader* shader;
	Texture* texture;
};