#pragma once
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Globals.h"
#include "Clock.h"

class SceneCamera
{
public:
	static glm::mat4 VIEW_MAT;
	static glm::mat4 PROJ_MAT;

	static void Activate();
private:
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static float cameraSpeed;
	static bool mouseIdle;
	static float lastX ;
	static float lastY;
	static float yaw;
	static float pitch;
	static float initXpos;
	static float initYpos;
	static glm::vec3 cameraPos;
	static glm::vec3 cameraFront;
	static glm::vec3 cameraUp;
};
