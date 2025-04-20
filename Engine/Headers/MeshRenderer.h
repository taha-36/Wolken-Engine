#pragma once
#include "Component.h"
#include "Mesh.h"
#include "Material.h"
struct DrawSettings
{
	bool useVertsColors = false;
};

class MeshRenderer : public Component
{
public:
	MeshRenderer() = default;

	DrawSettings drawSettings;
	Mesh* mesh = nullptr;
	Material* material = nullptr;

	void Render();
};
