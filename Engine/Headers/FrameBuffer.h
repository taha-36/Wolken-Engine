#pragma once
#include <vector>
#include <array>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Globals.h"
class FrameBuffer
{
public:
    GLuint FBO;
    GLuint RBO;

	FrameBuffer();
	void Activate();
};
