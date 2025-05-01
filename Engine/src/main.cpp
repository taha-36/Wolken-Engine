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
    Globals::Instance().InitializeDefaults();

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
    Globals::Instance().~Globals();
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
    glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
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