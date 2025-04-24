// SceneCamera.h
#pragma once
#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Globals.h"
#include "Clock.h"

class SceneCamera {
public:
    static void Activate();
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

    static glm::mat4 VIEW_MAT;
    static glm::mat4 PROJ_MAT;

private:
    static void ProcessKeyboardInput();
    static void ProcessMouseMovement();

    static float cameraSpeed;
    static bool firstMouse;
    static float lastX;
    static float lastY;
    static float yaw;
    static float pitch;
    static glm::vec3 cameraPos;
    static glm::vec3 cameraFront;
    static glm::vec3 cameraUp;
};