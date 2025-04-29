#pragma once
#include "GLFW/glfw3.h"
class Clock
{
public:
	static Clock& Instance()
	{
		static Clock instance;
		return instance;
	}
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	void Tick()
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - Clock::lastFrame;
		lastFrame = currentFrame;
	}
};
