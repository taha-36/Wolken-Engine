#pragma once
#include <glad/glad.h>
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
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
    }
    void ClearBuffer()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDisable(GL_DEPTH_TEST);
    }
    void Clean()
    {
        glDeleteFramebuffers(1, &sceneFrame.FBO);
        glDeleteRenderbuffers(1, &sceneFrame.RBO);
    }
private:
    Scene()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, sceneFrame.FBO);
        // Set up the sceneTexture (color output)
        glActiveTexture(GL_TEXTURE0);
        glGenTextures(1, &sceneTexture);
        glBindTexture(GL_TEXTURE_2D, sceneTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Globals::Instance().SCR_WIDTH, Globals::Instance().SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, sceneTexture, 0);  // Color output

        glActiveTexture(GL_TEXTURE1);
        glGenTextures(1, &idTexture);
        glBindTexture(GL_TEXTURE_2D, idTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_R32UI, Globals::Instance().SCR_WIDTH, Globals::Instance().SCR_HEIGHT, 0, GL_RED_INTEGER, GL_UNSIGNED_INT, NULL);
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
