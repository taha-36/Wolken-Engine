#pragma once
#include <GLFW/glfw3.h>
class Globals {
public:
    unsigned int SCR_WIDTH = 1920;
    unsigned int SCR_HEIGHT = 1080;
    GLFWwindow* WINDOW = nullptr;

    static Globals& Instance() {
        static Globals instance;
        return instance;
    }

    Globals(const Globals&) = delete;
    void operator=(const Globals&) = delete;

private:
    Globals() {}
};