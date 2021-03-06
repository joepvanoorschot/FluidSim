#pragma once

#include <glm/glm.hpp>
#include "body.h"

// rigid (or solid) shpere
class Sphere : public Body {
public:
	Sphere(glm::vec3 pos, float size, float m);

	glm::vec3 GetAngularVelocity(glm::vec3 contactpoint);
	glm::vec3 GetVelocity();
	glm::vec3 AbsoluteContactPoint(glm::vec3& relposition);

	bool collision(const glm::vec3& position, const glm::vec3& displacement, glm::vec3& contactPoint, float& penDepth, glm::vec3& normal);

	float size;
};
