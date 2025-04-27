#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <KHR/khrplatform.h>

#include <iostream>
#include <string>
#include <vector>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Mesh.h"
#include "Material.h"
#include "Texture.h"
#include "Entity.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "Clock.h"
#include "SceneCamera.h"
#include "Scene.h"
#include "Globals.h"
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
int init(GLFWwindow*& window);
int main(void)
{
    init(Globals::Instance().WINDOW);

    /* Shaders */
    Shader shader("assets/DefaultVert.glsl", "assets/DefaultFrag.glsl");
    Texture tex("assets/tex.jpg");
    Texture texWood("assets/wood.jpg");

    std::vector<float> poses = {
        //front
        -0.5f, -0.5f, 0.5f,     //bottom left
        -0.5f,  0.5f, 0.5f,     //top left
         0.5f, -0.5f, 0.5f,     //bottom right
         0.5f,  0.5f, 0.5f,     //top right

        //back
        -0.5f, -0.5f, -0.5f,     //bottom left
        -0.5f,  0.5f, -0.5f,     //top left
         0.5f, -0.5f, -0.5f,     //bottom right
         0.5f,  0.5f, -0.5f,     //top right

        //left
        -0.5f, -0.5f, -0.5f,     //bottom left
        -0.5f,  0.5f, -0.5f,     //top left
        -0.5f, -0.5f, 0.5f,     //bottom right
        -0.5f,  0.5f, 0.5f,     //top right

        //right
         0.5f, -0.5f, -0.5f,     //bottom left
         0.5f,  0.5f, -0.5f,     //top left
         0.5f, -0.5f, 0.5f,     //bottom right
         0.5f,  0.5f, 0.5f,     //top right

         //top
        -0.5f,  0.5f, 0.5f,     //bottom left
        -0.5f,  0.5f,-0.5f,     //top left
         0.5f,  0.5f, 0.5f,     //bottom right
         0.5f,  0.5f,-0.5f,     //top right

         //bottom
        -0.5f, -0.5f, 0.5f,     //bottom left
        -0.5f, -0.5f, -0.5f,     //top left
         0.5f, -0.5f, 0.5f,     //bottom right
         0.5f, -0.5f, -0.5f,     //top right
    };
    std::vector<float> uv = {
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,

        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,

        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,

        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,

        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,

        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
    };
    std::vector<float> colors = {
        1.0f, 1.0f, 0.5f,
        0.5f, 1.0f, 0.75f,
        0.6f, 1.0f, 0.2f,
        1.0f, 0.2f, 1.0f,

        1.0f, 1.0f, 0.5f,
        0.5f, 1.0f, 0.75f,
        0.6f, 1.0f, 0.2f,
        1.0f, 0.2f, 1.0f,

        1.0f, 1.0f, 0.5f,
        0.5f, 1.0f, 0.75f,
        0.6f, 1.0f, 0.2f,
        1.0f, 0.2f, 1.0f,

        1.0f, 1.0f, 0.5f,
        0.5f, 1.0f, 0.75f,
        0.6f, 1.0f, 0.2f,
        1.0f, 0.2f, 1.0f,

        1.0f, 1.0f, 0.5f,
        0.5f, 1.0f, 0.75f,
        0.6f, 1.0f, 0.2f,
        1.0f, 0.2f, 1.0f,

        1.0f, 1.0f, 0.5f,
        0.5f, 1.0f, 0.75f,
        0.6f, 1.0f, 0.2f,
        1.0f, 0.2f, 1.0f,
    };
    std::vector<float> colors2 = {
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,

    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,

    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,

    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,

    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,

    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    };
    std::vector<unsigned int> indices = {
        // Front face
        0, 1, 2,
        1, 3, 2,

        // Back face
        4, 6, 5,
        5, 6, 7,

        // Left face
        8, 9,10,
        9,11,10,

        // Right face
        12,14,13,
        13,14,15,

        // Top face
        16,17,18,
        17,19,18,

        // Bottom face
        20,22,21,
        21,22,23
    };

    Mesh mesh(poses, indices);
    Mesh mesh2(poses, indices);

    Material mat;
    Material mat2;
    Entity ent;
    Entity ent2;
    Entity ent3;

    MeshRenderer* mr = ent.AddComponent<MeshRenderer>();
    MeshRenderer* mr2 = ent2.AddComponent<MeshRenderer>();
    MeshRenderer* mr3 = ent3.AddComponent<MeshRenderer>();

    mr3->mesh = &mesh2;
    mr3->material = &mat2;

    mr2->mesh = &mesh2;
    mr2->material = &mat2;

    mr->mesh = &mesh;
    mr->material = &mat;

    mat.shader = &shader;
    mat.texture = &texWood;
    mat2.shader = &shader;
    mat2.texture = &texWood;

    mesh.SetUV(uv);
    mesh2.SetUV(uv);
    ent2.transform.Translate(glm::vec3(-1.0f, 0.0f, 5.0f));
    ent.transform.Translate(glm::vec3(1.0f, 0.0f, 5.0f));
    ent.transform.Rotate(glm::radians(45.0f), glm::vec3(1.0f));
    ent3.transform.Translate(glm::vec3(4.0f, 0.0f, 5.0f));

    //imgui shit
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(Globals::Instance().WINDOW, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(Globals::Instance().WINDOW))
    {
        glViewport(0, 0, Globals::Instance().SCR_WIDTH, Globals::Instance().SCR_HEIGHT);
        glfwPollEvents();

        Clock::Tick();
        SceneCamera::Activate();


        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        Scene::Instance().RenderScene();

        for (Entity* ent : Globals::Instance().SCENE_ENTS)
        {
            MeshRenderer* mr = ent->GetComponent<MeshRenderer>();
            if(mr != nullptr)
                mr->Render();
        }

        SceneCamera::ProcessTargetedObject();

        Scene::Instance().ClearBuffer();

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
            ImGuiID dock_id_right = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.25f, nullptr, &dock_main_id);
            ImGuiID dock_id_down = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Down, 0.25f, nullptr, &dock_main_id);
            ImGuiID dock_id_top = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Up, 0.25f, nullptr, &dock_main_id);

            // Dock windows
            ImGui::DockBuilderDockWindow("Scene", dock_id_top);
            ImGui::DockBuilderDockWindow("Inspector", dock_id_right);
            ImGui::DockBuilderDockWindow("Explorer", dock_id_down);

            ImGui::DockBuilderFinish(dockspace_id);
        }

        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);
        ImGui::End();

        ImGui::Begin("Scene", 0, ImGuiWindowFlags_NoScrollbar);
        if (ImGui::IsWindowHovered())
            Globals::Instance().Can_MoveScene = true;
        ImGui::Image((ImTextureID)(intptr_t)(Scene::Instance().sceneTexture), ImVec2(Globals::Instance().SCR_WIDTH, Globals::Instance().SCR_HEIGHT), ImVec2(0, 1), ImVec2(1, 0));
        ImGui::End();


        ImGui::Begin("Inspector", 0, ImGuiWindowFlags_NoScrollbar);
        ImGui::End();

        ImGui::Begin("Explorer", 0, ImGuiWindowFlags_NoScrollbar);
        ImGui::End();


        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(Globals::Instance().WINDOW);
    }
    Scene::Instance().Clean();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int init(GLFWwindow*& window)
{
    /* Initialize the library */
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }
    /* Set OpenGL version to 3.3 Core Profile */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(Globals::Instance().SCR_WIDTH, Globals::Instance().SCR_HEIGHT, "Wolken Engine", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // Load OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glEnable(GL_DEPTH_TEST);
}