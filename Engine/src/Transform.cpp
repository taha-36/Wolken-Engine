#include "Transform.h"

void Transform::Translate(glm::vec3 vec)
{
	worldPosition = worldPosition + vec;
}
void Transform::Rotate(float degrees, glm::vec3 dir)
{
	glm::quat rot = glm::angleAxis(degrees, dir);
	rotation = rotation * rot;
	eulerAngles = glm::degrees(glm::eulerAngles(rotation));
}
void Transform::UpdateTransform()
{

}