// SceneCamera.cpp
#include "SceneCamera.h"

glm::mat4 SceneCamera::VIEW_MAT = glm::mat4(1.0f);
glm::mat4 SceneCamera::PROJ_MAT = glm::perspective(
    glm::radians(45.0f),
    (float)Globals::Instance().SCR_WIDTH / (float)Globals::Instance().SCR_HEIGHT,
    0.1f,
    100.0f
);
float SceneCamera::cameraSpeed = 2.5f;
bool SceneCamera::firstMouse = true;
float SceneCamera::lastX = Globals::Instance().SCR_WIDTH / 2.0f;
float SceneCamera::lastY = Globals::Instance().SCR_HEIGHT / 2.0f;
float SceneCamera::yaw = 90.0f;
float SceneCamera::pitch = 0.0f;
glm::vec3 SceneCamera::cameraPos = glm::vec3(0.0f, 0.0f, -3.0f);
glm::vec3 SceneCamera::cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);
glm::vec3 SceneCamera::cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

void SceneCamera::Activate()
{
    ImGuiWindow* window = ImGui::FindWindowByName("Scene");
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

void SceneCamera::ProcessKeyboardInput()
{
    if (glfwGetKey(Globals::Instance().WINDOW, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * Clock::deltaTime * cameraFront;
    if (glfwGetKey(Globals::Instance().WINDOW, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * Clock::deltaTime * cameraFront;
    if (glfwGetKey(Globals::Instance().WINDOW, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * Clock::deltaTime;
    if (glfwGetKey(Globals::Instance().WINDOW, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * Clock::deltaTime;
}

void SceneCamera::ProcessMouseMovement()
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

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;


    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}
void SceneCamera::ProcessTargetedObject()
{
    if (glfwGetMouseButton(Globals::Instance().WINDOW, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        double xpos, ypos;
        glfwGetCursorPos(Globals::Instance().WINDOW, &xpos, &ypos);

        // Convert ImGui Y coordinate system to OpenGL's Y coordinate system
        int windowHeight;
        glfwGetFramebufferSize(Globals::Instance().WINDOW, nullptr, &windowHeight);
        ypos = windowHeight - ypos;
        glBindBuffer(GL_FRAMEBUFFER, Scene::Instance().sceneFrame.FBO);
        glReadBuffer(GL_COLOR_ATTACHMENT1);

        GLuint pixel;
        glReadPixels(xpos, ypos, 1, 1, GL_RED_INTEGER, GL_UNSIGNED_INT, &pixel);

        std::cout << pixel << std::endl;
    }
}