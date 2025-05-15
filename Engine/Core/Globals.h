#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Mesh.h"
#include "Material.h"
#include "Model.h"
class Entity;
class Globals {
public:
    unsigned int SCR_WIDTH;
    unsigned int SCR_HEIGHT;

    unsigned int sceneWidth;
    unsigned int sceneHeight;
    
    bool Can_MoveScene = false;
    std::vector<Entity*> SCENE_ENTS;

    GLFWwindow* WINDOW = nullptr;
    Entity* selectedEnt = nullptr;

    //Defaults
    Mesh* cube = nullptr;
    Mesh* cylinder = nullptr;
    Mesh* sphere = nullptr;

    Material* defaultMaterial = nullptr;

    Shader* defaultShader = nullptr;

    static Globals& Instance() {
        static Globals instance;
        return instance;
    }

    void InitializeDefaults()
    {
        Model* cubeModel = new Model("assets/cube.fbx");
        Model* sphereModel = new Model("assets/sphere.fbx");
        Model* cylinderModel = new Model("assets/cylinder.fbx");

        this->cube = cubeModel->meshes[0];
        this->sphere = sphereModel->meshes[0];
        this->cylinder = cylinderModel->meshes[0];

        //Set Default Shader
        this->defaultShader = new Shader("assets/DefaultShader.json", "assets/DefaultVert.glsl", "assets/DefaultFrag.glsl");

        //Set Default Material
        this->defaultMaterial = new Material("assets/DefaultMaterial.json");
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