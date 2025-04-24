#include "Clock.h"

float Clock::deltaTime = 0.0f;
float Clock::lastFrame = 0.0f;

void Clock::Tick()
{
    float currentFrame = glfwGetTime();
    Clock::deltaTime = currentFrame - Clock::lastFrame;
    Clock::lastFrame = currentFrame;
}