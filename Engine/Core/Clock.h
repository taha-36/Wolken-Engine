#pragma once
#include "GLFW/glfw3.h"
class Clock
{
public:
	static float deltaTime;
	static float lastFrame;

	static void Tick();
};
