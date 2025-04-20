#include "SceneCamera.h"
#include "Globals.h"
glm::mat4 SceneCamera::VIEW_MAT = glm::mat4(1.0f);
glm::mat4 SceneCamera::PROJ_MAT = glm::perspective(glm::radians(45.0f), (float)Globals::Instance().SCR_WIDTH / (float)Globals::Instance().SCR_HEIGHT, 0.1f, 100.0f);

float SceneCamera::cameraSpeed = 2.5f;
bool SceneCamera::mouseIdle = true;
float SceneCamera::lastX = Globals::Instance().SCR_WIDTH / 2;
float SceneCamera::lastY = Globals::Instance().SCR_HEIGHT / 2;
float SceneCamera::yaw = 90.0f;
float SceneCamera::pitch = 0.0f;
float SceneCamera::initXpos = 0.0f;
float SceneCamera::initYpos = 0.0f;
glm::vec3 SceneCamera::cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 SceneCamera::cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);
glm::vec3 SceneCamera::cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

void SceneCamera::Activate()
{
    if (glfwGetMouseButton(Globals::Instance().WINDOW, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
        if (glfwGetKey(Globals::Instance().WINDOW, GLFW_KEY_W) == GLFW_PRESS)
            cameraPos += SceneCamera::cameraSpeed * Clock::deltaTime * cameraFront;
        if (glfwGetKey(Globals::Instance().WINDOW, GLFW_KEY_S) == GLFW_PRESS)
            cameraPos -= SceneCamera::cameraSpeed * Clock::deltaTime * cameraFront;
        if (glfwGetKey(Globals::Instance().WINDOW, GLFW_KEY_A) == GLFW_PRESS)
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * SceneCamera::cameraSpeed * Clock::deltaTime;
        if (glfwGetKey(Globals::Instance().WINDOW, GLFW_KEY_D) == GLFW_PRESS)
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * SceneCamera::cameraSpeed * Clock::deltaTime;
        glfwSetCursorPosCallback(Globals::Instance().WINDOW, SceneCamera::mouse_callback);
    }
    else
    {
        glfwSetCursorPosCallback(Globals::Instance().WINDOW, nullptr);
        mouseIdle = true;
    }

    VIEW_MAT = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void SceneCamera::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (mouseIdle)
    {
        lastX = xpos;
        lastY = ypos;
        mouseIdle = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 20.0f;
    xoffset *= sensitivity * Clock::deltaTime;
    yoffset *= sensitivity * Clock::deltaTime;

    yaw += xoffset;
    pitch += yoffset;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}