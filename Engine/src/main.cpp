#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <KHR/khrplatform.h>
#include <iostream>
#include "Shader.h"
#include "Mesh.h"
#include "Material.h"
#include "Texture.h"
#include "Entity.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "Clock.h"
#include "Globals.h"
#include "UI.h"
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

    Material defaultMaterial;
    Entity ent;
    Entity ent2;
    Entity ent3;

    MeshRenderer* mr = ent.AddComponent<MeshRenderer>();
    MeshRenderer* mr2 = ent2.AddComponent<MeshRenderer>();
    MeshRenderer* mr3 = ent3.AddComponent<MeshRenderer>();

    mr3->mesh = &mesh2;
    mr3->material = &defaultMaterial;

    mr2->mesh = &mesh2;
    mr2->material = &defaultMaterial;

    mr->mesh = &mesh;
    mr->material = &defaultMaterial;

    defaultMaterial.shader = &shader;
    defaultMaterial.texture = &texWood;

    mesh.SetUV(uv);
    mesh2.SetUV(uv);
    ent2.transform.Translate(glm::vec3(-1.0f, 0.0f, 5.0f));
    ent.transform.Translate(glm::vec3(1.0f, 0.0f, 5.0f));
    ent.transform.Rotate(glm::radians(45.0f), glm::vec3(1.0f));
    ent3.transform.Translate(glm::vec3(4.0f, 0.0f, 5.0f));

    UI::Instance().Initialize();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(Globals::Instance().WINDOW))
    {
        glfwPollEvents();
        glfwSetFramebufferSizeCallback(Globals::Instance().WINDOW, framebuffer_size_callback);

        Clock::Instance().Tick();
        UI::Instance().Render();

        glfwSwapBuffers(Globals::Instance().WINDOW);
    }
    UI::Instance().CleanUI();
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, Globals::Instance().sceneWidth, Globals::Instance().sceneHeight);
    if (width != 0 || height != 0)
    {
        Globals::Instance().SCR_WIDTH = width;
        Globals::Instance().SCR_HEIGHT = height;
    }
}

int init(GLFWwindow*& window)
{
    Globals::Instance().SCR_WIDTH = 1920;
    Globals::Instance().SCR_HEIGHT = 1080;
    Globals::Instance().sceneWidth = Globals::Instance().SCR_WIDTH;
    Globals::Instance().sceneHeight = Globals::Instance().SCR_HEIGHT;

    /* Initialize the library */
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }
    /* Set OpenGL version to 3.3 Core Profile */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(Globals::Instance().SCR_WIDTH, Globals::Instance().SCR_HEIGHT, "Wolken Engine", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);

    // Load OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glEnable(GL_DEPTH_TEST);
}