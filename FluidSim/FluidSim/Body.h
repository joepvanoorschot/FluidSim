#pragma once

#include <glm/glm.hpp>
#include <glload/gl_3_3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Axis aligned bounding box for the particles to stay within
class Body {
public:
	virtual glm::vec3 GetAngularVelocity(glm::vec3 contactpoint) = 0;
	virtual glm::vec3 GetVelocity() = 0;
	virtual glm::vec3 contactNormal() = 0;
	virtual glm::vec3 absoluteContactPoint(glm::vec3& relposition) = 0;
	virtual bool collision(const glm::vec3& position, const glm::vec3& newposition, glm::vec3& contactPoint, float& penDepth, glm::vec3& normal) = 0;


	glm::vec3	center;
	glm::vec3	velocity;
	glm::vec3	forceAccum;		// Force accumulator
	float		mass;
};