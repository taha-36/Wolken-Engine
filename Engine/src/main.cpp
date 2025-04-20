#include "imgui.h"
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
#include "Globals.h"
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
int init(GLFWwindow*& window);

int main(void)
{
    init(Globals::Instance().WINDOW);

    /* Shaders */
    Shader shader("assets/vertex_core.glsl", "assets/fragment_core.glsl");
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

    Mesh mesh(poses, indices, colors);
    Mesh mesh2(poses, indices);
    Material mat;
    Entity ent;
    Entity ent2;
    MeshRenderer mr2 = ent2.AddComponent<MeshRenderer>();
    MeshRenderer mr = ent.AddComponent<MeshRenderer>();

    mr2.mesh = &mesh2;
    mr2.material = &mat;
    mr.mesh = &mesh;
    mr.material = &mat;

    mat.shader = &shader;
    mat.texture = &texWood;
    mesh.SetUV(uv);
    mesh2.SetUV(uv);
    ent2.transform.Translate(glm::vec3(-1.0f, 0.0f, 5.0f));
    ent.transform.Translate(glm::vec3(1.0f, 0.0f, 5.0f));
    ent.transform.Rotate(glm::radians(45.0f), glm::vec3(1.0f));

    //imgui shit
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    // Set up ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(Globals::Instance().WINDOW, true);
    ImGui_ImplOpenGL3_Init("#version 130");


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(Globals::Instance().WINDOW))
    {
        Clock::Tick();
        SceneCamera::Activate();

       /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        mr.Render();
        mr2.Render();

        // Start new ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Simple ImGui window
        ImGui::Begin("Hello, ImGui!");
        ImGui::Text("This is an ImGui window.");
        if (ImGui::Button("Close")) {
            break;  // Close the window
        }
        ImGui::End();

        // Render ImGui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(Globals::Instance().WINDOW);

        /* Poll for and process events */
        glfwPollEvents();
    }
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

    // 🛑 ADD THIS: Load OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glEnable(GL_DEPTH_TEST);
}