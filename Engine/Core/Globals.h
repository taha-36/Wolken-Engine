#pragma once
#include <GLFW/glfw3.h>
#include <vector>

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

    static Globals& Instance() {
        static Globals instance;
        return instance;
    }

private:
    Globals() {
    }
};