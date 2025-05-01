#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <iostream>
#include "Component.h"
class Transform : public Component
{
public:
	Transform() = default;
	~Transform() = default;

	glm::vec3 worldPosition = glm::vec3(0.0f);
	glm::vec3 eulerAngles = glm::vec3(0.0f);
	glm::vec3 worldScale = glm::vec3(1.0f);

	glm::vec3 localPosition = glm::vec3(0.0f);

	glm::quat rotation = glm::quat(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	void Translate(glm::vec3 vec);
	void Rotate(float degrees, glm::vec3 dir);
	void UpdateTransform();
};
