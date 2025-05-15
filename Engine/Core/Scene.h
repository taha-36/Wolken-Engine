#pragma once
#include <glad/glad.h>
#include "ImGui.h"
#include "FrameBuffer.h"
#include "Shader.h"
class Scene
{
public:
    GLuint sceneTexture = 0;
    GLuint idTexture = 0;
    FrameBuffer sceneFrame;

    static Scene& Instance() {
        static Scene instance;
        return instance;
    }

    void RenderScene()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, sceneFrame.FBO);
        glViewport(0, 0, Globals::Instance().sceneWidth, Globals::Instance().sceneHeight);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
    }
    void ClearBuffer()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        glDisable(GL_DEPTH_TEST);
    }
    void Clean()
    {
        glDeleteFramebuffers(1, &sceneFrame.FBO);
        glDeleteRenderbuffers(1, &sceneFrame.RBO);
    }
    void ResizeFrameBuffer()
    {
        // 1. Bind the framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, sceneFrame.FBO);

        glDeleteRenderbuffers(1, &sceneFrame.RBO);
        glGenRenderbuffers(1, &sceneFrame.RBO);
        glBindRenderbuffer(GL_RENDERBUFFER, sceneFrame.RBO);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Globals::Instance().sceneWidth, Globals::Instance().sceneHeight);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, sceneFrame.RBO);

        // 2. Detach old textures first
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, 0, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, 0, 0);

        // 3. Delete old textures
        glDeleteTextures(1, &sceneTexture);
        glDeleteTextures(1, &idTexture);

        // 4. Create new textures
        glGenTextures(1, &sceneTexture);
        glBindTexture(GL_TEXTURE_2D, sceneTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Globals::Instance().sceneWidth, Globals::Instance().sceneHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, sceneTexture, 0);

        // Same for idTexture
        glGenTextures(1, &idTexture);
        glBindTexture(GL_TEXTURE_2D, idTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_R32UI, Globals::Instance().sceneWidth, Globals::Instance().sceneHeight, 0, GL_RED_INTEGER, GL_UNSIGNED_INT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, idTexture, 0);

        // 5. Set draw buffers again (needed)
        GLenum drawBuffers[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
        glDrawBuffers(2, drawBuffers);
    }
    void ProcessTargetedObject()
    {
        if (glfwGetMouseButton(Globals::Instance().WINDOW, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && Globals::Instance().Can_MoveScene)
        {
            double xpos, ypos;
            double i, j;
            double w = ImGui::GetWindowSize().x;
            double h = ImGui::GetWindowSize().y;
            double f = ImGui::GetWindowPos().x;
            double z = ImGui::GetWindowPos().y;
            glfwGetCursorPos(Globals::Instance().WINDOW, &xpos, &ypos);

            i = xpos - f - 8;
            j = h - (ypos - z) - 10;

            glBindFramebuffer(GL_FRAMEBUFFER, Scene::Instance().sceneFrame.FBO);
            glReadBuffer(GL_COLOR_ATTACHMENT1);

            Globals::Instance().selectedEnt = nullptr;
            GLuint pixel;
            glReadPixels(i, j, 1, 1, GL_RED_INTEGER, GL_UNSIGNED_INT, &pixel);

            for (Entity* var : Globals::Instance().SCENE_ENTS) 
            {
                if (pixel == var->id)
                {
                    Globals::Instance().selectedEnt = var;
                    break;
                }
            }
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }
    }
private:
    Scene()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, sceneFrame.FBO);

        glGenTextures(1, &sceneTexture);
        glBindTexture(GL_TEXTURE_2D, sceneTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Globals::Instance().sceneWidth, Globals::Instance().sceneHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, sceneTexture, 0);  // Color output

        glGenTextures(1, &idTexture);
        glBindTexture(GL_TEXTURE_2D, idTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_R32UI, Globals::Instance().sceneWidth, Globals::Instance().sceneHeight, 0, GL_RED_INTEGER, GL_UNSIGNED_INT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, idTexture, 0);  // Color output

        GLenum drawBuffers[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
        glDrawBuffers(2, drawBuffers);  // Ensure we're drawing to both attachments
        GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (status != GL_FRAMEBUFFER_COMPLETE) {
            std::cout << "Framebuffer not complete! Status: " << status << std::endl;
        }
    }
};
