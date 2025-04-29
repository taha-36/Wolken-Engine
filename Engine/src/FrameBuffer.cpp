#include "FrameBuffer.h"
FrameBuffer::FrameBuffer()
{
    FBO = 0;
    RBO = 0;
    FrameBuffer::Activate();
}
void FrameBuffer::Activate()
{
    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);

    glGenRenderbuffers(1, &RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Globals::Instance().sceneWidth, Globals::Instance().sceneHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);
}