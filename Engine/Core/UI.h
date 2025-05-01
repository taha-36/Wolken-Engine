#pragma once
#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Globals.h"
#include "SceneCamera.h"
#include "MeshRenderer.h"
class UI
{
public:
	static UI& Instance()
	{
		static UI instance;
		return instance;
	}

	void Initialize()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
        //io.IniFilename = nullptr;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(Globals::Instance().WINDOW, true);
		ImGui_ImplOpenGL3_Init("#version 330 core");
	}
	void Render()
	{
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (Globals::Instance().sceneWidth != 0 && Globals::Instance().sceneHeight != 0)
        {
            SceneCamera::Instance().Activate();

            Scene::Instance().RenderScene();

            for (Entity* ent : Globals::Instance().SCENE_ENTS)
            {
                MeshRenderer* mr = ent->GetComponent<MeshRenderer>();
                if (mr != nullptr)
                    mr->Render();
            }

            Scene::Instance().ClearBuffer();
        }
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);

        ImGuiWindowFlags host_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoBringToFrontOnFocus |
            ImGuiWindowFlags_NoNavFocus;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpaceHost", nullptr, host_flags);
        ImGui::PopStyleVar(3);

        // 2. Create the dockspace
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        if (!ImGui::DockBuilderGetNode(dockspace_id))
        {
            // First run - setup docking layout
            ImGui::DockBuilderRemoveNode(dockspace_id); // Clear any existing layout
            ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_PassthruCentralNode);
            ImGui::DockBuilderSetNodeSize(dockspace_id, viewport->WorkSize);

            // Split the dockspace into two nodes
            ImGuiID left, right;
            ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Left, 0.5f, &left, &right);

            ImGuiID dock_main_id = dockspace_id;
            ImGuiID dock_id_left = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.25f, nullptr, &dock_main_id);
            ImGuiID dock_id_right = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.25f, nullptr, &dock_main_id);
            ImGuiID dock_id_top = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Up, 0.25f, nullptr, &dock_main_id);
            ImGuiID dock_id_down = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Down, 0.25f, nullptr, &dock_main_id);

            // Dock windows
            ImGui::DockBuilderDockWindow("Explorer", dock_id_down);
            ImGui::DockBuilderDockWindow("Scene", dock_id_top);
            ImGui::DockBuilderDockWindow("Inspector", dock_id_right);
            ImGui::DockBuilderDockWindow("Entities", dock_id_left);

            ImGui::DockBuilderFinish(dockspace_id);
        }

        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);
        ImGui::End();

        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("Add"))
            {
                if (ImGui::MenuItem("Empty Entity")) {
                    // Handle open
                    AddEntity();
                }
                if (ImGui::MenuItem("Cube")) {
                    AddCube();
                }
                if (ImGui::MenuItem("Material", "Ctrl+S")) {
                    // Handle save
                }
                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }

        ImGui::Begin("Scene", 0, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
        if (ImGui::IsWindowHovered())
        {
            Globals::Instance().Can_MoveScene = true;
        }
        ImGui::Image((ImTextureID)(Scene::Instance().sceneTexture), ImVec2(Globals::Instance().sceneWidth, Globals::Instance().sceneHeight), ImVec2(0, 1), ImVec2(1, 0));

        ImVec2 windowPos = ImGui::GetWindowPos();
        ImVec2 contentMin = ImGui::GetWindowContentRegionMin();
        ImVec2 contentMax = ImGui::GetWindowContentRegionMax();

        ImVec2 imageTopLeft = ImVec2(windowPos.x + contentMin.x, windowPos.y + contentMin.y);
        ImVec2 imageBottomRight = ImVec2(windowPos.x + contentMax.x, windowPos.y + contentMax.y);

        float imageWidth = contentMax.x - contentMin.x;
        float imageHeight = contentMax.y - contentMin.y;

        Scene::Instance().ProcessTargetedObject();

        ImGui::End();


        ImGui::Begin("Inspector", 0, ImGuiWindowFlags_NoScrollbar);
        if (Globals::Instance().selectedEnt != nullptr)
        {
            std::vector<Component*> components = Globals::Instance().selectedEnt->GetAllComponents();
            // Transform section
            ImGui::Text("Transform");
            ImGui::DragFloat3("Position", &Globals::Instance().selectedEnt->transform.worldPosition.x, 0.1f);
            if (ImGui::DragFloat3("Rotation", &Globals::Instance().selectedEnt->transform.eulerAngles.x, 0.1f))
            {
                Globals::Instance().selectedEnt->transform.rotation = glm::quat(glm::radians(Globals::Instance().selectedEnt->transform.eulerAngles));
            }
            ImGui::DragFloat3("Scale", &Globals::Instance().selectedEnt->transform.worldScale.x, 0.1f);
        }
        ImGui::End();

        ImGui::Begin("Explorer", 0, ImGuiWindowFlags_NoScrollbar);
        ImGui::End();

        ImGui::Begin("Entities", 0, ImGuiWindowFlags_NoScrollbar);
        std::vector<Entity*> sceneEnts = Globals::Instance().SCENE_ENTS;

        for (Entity* entity : sceneEnts) 
        {
            // Create a unique identifier for each entity
            std::string label = "Entity " + std::to_string(entity->id);
            if (ImGui::Button(label.c_str()))
            {
                Globals::Instance().selectedEnt = entity; // Select on click
            }
        }
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        //Resize Frame Buffer If Needed
        if (Globals::Instance().sceneWidth != imageWidth || Globals::Instance().sceneHeight != imageHeight)
        {
            Globals::Instance().sceneWidth = imageWidth;
            Globals::Instance().sceneHeight = imageHeight;
            if (imageWidth != 0 && imageHeight != 0)
            {
                Scene::Instance().ResizeFrameBuffer();
            }
        }
	}
    void CleanUI()
    {
        Scene::Instance().Clean();
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
    void AddEntity()
    {
        Entity* ent = new Entity();
    }
    void AddCube()
    {
        Entity* ent = new Entity();
        MeshRenderer* meshRenderer = ent->AddComponent<MeshRenderer>();
        meshRenderer->BindMesh(Globals::Instance().cube);
        meshRenderer->material = Globals::Instance().defaultMaterial;
    }
private:
	UI() {}
};
