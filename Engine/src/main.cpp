#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <KHR/khrplatform.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "Shader.h"
#include "Mesh.h"
#include "Material.h"
#include "Texture.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
int main(void)
{
    int success;
    char infoLog[512];
    GLFWwindow* window;

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
    window = glfwCreateWindow(1280, 720, "Wolken Engine", NULL, NULL);
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

    /* Set the clear color */
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);


    /* Shaders */
    Shader shader("assets/vertex_core.glsl", "assets/fragment_core.glsl");
    Shader shader2("assets/vertex_core.glsl", "assets/fragment_core.glsl");
    Texture tex("assets/tex.jpg");
    Texture texWood("assets/wood.jpg");
    ///* vertex array */
    std::vector<float> poses = {
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
    };
    std::vector<float> uv = {
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f
    };

    std::vector<float> poses2 = {
     0.85f, -0.66f, 0.0f,
     0.5f,  0.69f, 0.0f,
     0.72f, -0.5f, 0.0f,
     0.88f,  0.5f, 0.0f,
    };

    std::vector<float> colors = {
        1.0f, 1.0f, 0.5f,
        0.5f, 1.0f, 0.75f,
        0.6f, 1.0f, 0.2f,
        1.0f, 0.2f, 1.0f
    };

    ///* indices array */
    std::vector<unsigned int> indices =
    {
        0, 1, 2,
        2, 1, 3
    };
    std::vector<unsigned int> indices2 =
    {
        0, 1, 2,
        2, 1, 3
    };

    Mesh mesh(poses, indices);
    Mesh mesh2(poses2, indices);

    Material mat;
    Material mat2;

    mat2.shader = &shader2;
    mat.shader = &shader;
    mat.texture = &tex;
    mat2.texture = &texWood;


    mesh.material = &mat;
    mesh.SetUV(uv);
    mesh2.material = &mat2;
    mesh2.SetUV(uv);


    /* resize window content */
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //position multiplier
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
       /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        mesh.Render();
        mesh2.Render();
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

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