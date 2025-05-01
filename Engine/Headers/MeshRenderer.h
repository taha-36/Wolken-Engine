#pragma once
#include "Mesh.h"
#include "Entity.h"
#include "SceneCamera.h"
#include "Component.h"
#include "Material.h"
struct DrawSettings
{
	bool useVertsColors = false;
};

class MeshRenderer : public Component
{
public:

	unsigned int VAO;
	unsigned int posesVBO;
	unsigned int colorsVBO;
	unsigned int uvVBO;
	unsigned int EBO;

	DrawSettings drawSettings;
	Material* material = nullptr;

	MeshRenderer();
	~MeshRenderer();
	void Render();
	void BindMesh(Mesh* ptr);
	void RecalculateUV();
private:
	Mesh* mesh = nullptr;
};
