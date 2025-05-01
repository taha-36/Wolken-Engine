#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Mesh.h"
#include "Material.h"

class Entity;

class Globals {
public:
    unsigned int SCR_WIDTH = 800;
    unsigned int SCR_HEIGHT = 800;

    unsigned int sceneWidth = 800;
    unsigned int sceneHeight = 800;
    
    bool Can_MoveScene = false;
    std::vector<Entity*> SCENE_ENTS;

    GLFWwindow* WINDOW = nullptr;
    Entity* selectedEnt = nullptr;

    //Defaults
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
    Mesh* cube = nullptr;

    Material* defaultMaterial = nullptr;

    Shader* defaultShader = nullptr;

    static Globals& Instance() {
        static Globals instance;
        return instance;
    }

    void InitializeDefaults()
    {
        //Set Default Cube
        this->cube = new Mesh(poses, indices);
        this->cube->uv = uv;


        //Set Default Shader
        this->defaultShader = new Shader("assets/DefaultVert.glsl", "assets/DefaultFrag.glsl");

        //Set Default Material
        this->defaultMaterial = new Material();
        this->defaultMaterial->shader = this->defaultShader;
    }
    ~Globals() {
        CleanupResources();
    }
private:
    Globals() {}
    void CleanupResources() {
        delete cube;
        delete defaultShader;
        delete defaultMaterial;
        cube = nullptr;
        defaultShader = nullptr;
        defaultMaterial = nullptr;
    }
};