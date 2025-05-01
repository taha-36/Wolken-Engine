#pragma once
#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Globals.h"
#include "Clock.h"
#include "Entity.h"
#include "Scene.h"

class SceneCamera {
public:

    glm::mat4 VIEW_MAT;
    glm::mat4 PROJ_MAT;
    float cameraSpeed = 2.5f;
    bool firstMouse = true;
    float lastX = Globals::Instance().sceneWidth / 2.0f;
    float lastY = Globals::Instance().sceneHeight / 2.0f;
    float yaw = 90.0f;
    float pitch = 0.0f;
    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, -3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    static SceneCamera& Instance() {
        static SceneCamera instance;
        return instance;
    }
    void Activate()
    {
        VIEW_MAT = glm::mat4(1.0f);
        PROJ_MAT = glm::perspective(
            glm::radians(45.0f),
            (float)Globals::Instance().sceneWidth / (float)Globals::Instance().sceneHeight,
            0.1f,
            100.0f
        );
        // Only process input if right mouse button is pressed
        if (glfwGetMouseButton(Globals::Instance().WINDOW, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS && Globals::Instance().Can_MoveScene)
        {
            ProcessKeyboardInput();
            ProcessMouseMovement();
        }
        else
        {
            firstMouse = true;
            Globals::Instance().Can_MoveScene = false;
        }
        VIEW_MAT = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    }
    void ProcessKeyboardInput()
    {
        if (glfwGetKey(Globals::Instance().WINDOW, GLFW_KEY_W) == GLFW_PRESS)
            cameraPos += cameraSpeed * Clock::Instance().deltaTime * cameraFront;
        if (glfwGetKey(Globals::Instance().WINDOW, GLFW_KEY_S) == GLFW_PRESS)
            cameraPos -= cameraSpeed * Clock::Instance().deltaTime * cameraFront;
        if (glfwGetKey(Globals::Instance().WINDOW, GLFW_KEY_A) == GLFW_PRESS)
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * Clock::Instance().deltaTime;
        if (glfwGetKey(Globals::Instance().WINDOW, GLFW_KEY_D) == GLFW_PRESS)
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * Clock::Instance().deltaTime;
    }
    void ProcessMouseMovement()
    {
        double xpos, ypos;
        glfwGetCursorPos(Globals::Instance().WINDOW, &xpos, &ypos);

        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
        lastX = xpos;
        lastY = ypos;

        float sensitivity = 40.0f;
        xoffset *= sensitivity * Clock::Instance().deltaTime;
        yoffset *= sensitivity * Clock::Instance().deltaTime;

        yaw += xoffset;
        pitch += yoffset;


        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront = glm::normalize(front);
    }
};