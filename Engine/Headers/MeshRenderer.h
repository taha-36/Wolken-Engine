#pragma once
#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
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
	void Serialize() override;
	void Render();
	void BindMesh(Mesh* ptr);
	void RecalculateUV();
private:
	Mesh* mesh = nullptr;
};
