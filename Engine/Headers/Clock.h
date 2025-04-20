#pragma once
class Clock
{
public:
	static float deltaTime;
	static float lastFrame;

	static void Tick();
};
