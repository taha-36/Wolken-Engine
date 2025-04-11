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

std::string loadShaderSrc(const char* filename);
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


    //Shaders

    //compile vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    std::string vertShaderSrc = loadShaderSrc("Assets/vertex_core.glsl");
    const GLchar* vertShader = vertShaderSrc.c_str();
    glShaderSource(vertexShader, 1, &vertShader, NULL);
    glCompileShader(vertexShader);

    //catch error
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "Error with vertex shader com: " << infoLog << std::endl;
    }

    //compile fragment shader
    unsigned int fragmentShaders[2];
    fragmentShaders[0] = glCreateShader(GL_FRAGMENT_SHADER);
    std::string fragmentShaderSrc = loadShaderSrc("Assets/fragment_core.glsl");
    const GLchar* fragShader = fragmentShaderSrc.c_str();
    glShaderSource(fragmentShaders[0], 1, &fragShader, NULL);
    glCompileShader(fragmentShaders[0]);

    // Catch Error
    glGetShaderiv(fragmentShaders[0], GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShaders[0], 512, NULL, infoLog);
        std::cout << "Error with frag shader com: " << infoLog << std::endl;
    }

    //compile fragment shader 2
    fragmentShaders[1] = glCreateShader(GL_FRAGMENT_SHADER);
    fragmentShaderSrc = loadShaderSrc("Assets/fragment_core2.glsl");
    fragShader = fragmentShaderSrc.c_str();
    glShaderSource(fragmentShaders[1], 1, &fragShader, NULL);
    glCompileShader(fragmentShaders[1]);

    // Catch Error
    glGetShaderiv(fragmentShaders[1], GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShaders[1], 512, NULL, infoLog);
        std::cout << "Error with frag shader com: " << infoLog << std::endl;
    }


    //create program 1
    unsigned int shaderPrograms[2];
    shaderPrograms[0] = glCreateProgram();

    glAttachShader(shaderPrograms[0], vertexShader);
    glAttachShader(shaderPrograms[0], fragmentShaders[0]);
    glLinkProgram(shaderPrograms[0]);

    // catch error
    glGetProgramiv(shaderPrograms[0], GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderPrograms[0], 512, NULL, infoLog);
        std::cout << "Linking error : " << infoLog << std::endl;
    }

    //create program 2
    shaderPrograms[1] = glCreateProgram();

    glAttachShader(shaderPrograms[1], vertexShader);
    glAttachShader(shaderPrograms[1], fragmentShaders[1]);
    glLinkProgram(shaderPrograms[1]);

    // catch error
    glGetProgramiv(shaderPrograms[1], GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderPrograms[1], 512, NULL, infoLog);
        std::cout << "Linking error : " << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShaders[0]);
    glDeleteShader(fragmentShaders[1]);

    // vertex array
    float vertices[] = {
        //positions                         //colors
         0.5f, 0.5f, 0.0f,                  1.0f, 1.0f, 0.5f,
        -0.5f, 0.5f, 0.0f,                  0.5f, 1.0f, 0.75f,
        -0.5f, -0.5f, 0.0f,                 0.6f, 1.0f, 0.2f,
         0.5f, -0.5f, 0.0f,                 1.0f, 0.2f, 1.0f
    };
    unsigned int indices[] =
    {
        0, 1, 2,
        2, 3, 0
    };

    // VAO, VBO
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // bind VAO
    glBindVertexArray(VAO);

    // bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // set attribute pointer

    //positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //colors
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // set up EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // draw shapes
        glBindVertexArray(VAO);

        //first triangle
        glUseProgram(shaderPrograms[0]);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        //second triangle
        glUseProgram(shaderPrograms[0]);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3 * sizeof(unsigned int)));


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VAO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate();
    return 0;
}

std::string loadShaderSrc(const char* filename)
{
    std::ifstream file;
    std::stringstream buf;

    std::string ret = "";

    file.open(filename);

    if (file.is_open())
    {
        buf << file.rdbuf();
        ret = buf.str();
    }
    else
    {
        std::cout << "Couldn't open " << filename << std::endl;
    }
    file.close();

    return ret;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}