#include "sphere.h"
#include "util.h"
#include <glload/gl_3_3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



sphere::sphere(glm::vec3 pos, float size){
	position = pos;
	this->size = size;
}

const GLshort cubeIndices[] = {
	2, 3, 6, 3, 7, 6,	// Front face
	0, 4, 5, 1, 0, 5,	// Back face
	0, 1, 2, 1, 3, 2,	// Top face
	6, 7, 5, 6, 5, 4,	// Bottom face
	0, 2, 4, 2, 6, 4,	// Left face
	3, 1, 5, 3, 5, 7,	// Right face
};

void sphere::draw( GLuint mvpMatrixUniform,		
GLuint modelViewMatrixUniform,	
GLuint normalMatrixUniform,		
glm::mat4 modelMatrix,			
glm::mat4 viewMatrix,			
glm::mat4 projectionMatrix,	
glm::mat4 mvpMatrix,			
glm::mat4 modelViewMatrix,		
glm::mat4 normalMatrix			){
	modelMatrix = glm::scale(glm::mat4(1.f), glm::vec3(size, size, size));
	modelMatrix = glm::translate(modelMatrix, position / size);
	mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;
	glUniformMatrix4fv(mvpMatrixUniform, 1, GL_FALSE, glm::value_ptr(mvpMatrix));
	modelViewMatrix = viewMatrix * modelMatrix;
	glUniformMatrix4fv(modelViewMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelViewMatrix));
	normalMatrix = glm::transpose(glm::inverse(modelViewMatrix));
	glUniformMatrix4fv(normalMatrixUniform, 1, GL_FALSE, glm::value_ptr(normalMatrix));

	glDrawElements(GL_TRIANGLES, sizeof(cubeIndices) / sizeof(GLshort), GL_UNSIGNED_SHORT, 0);
}

glm::vec3 sphere::GetAngularVelocity(glm::vec3 contactpoint){
	return glm::vec3(0.f,0.f,0.f); 
}

glm::vec3 sphere::GetVelocity(){
	return velocity; 
}

glm::vec3 sphere::contactNormal(){
	return glm::vec3(0.f, 0.f, 0.f);
}

bool sphere::collision(const glm::vec3& parposition, glm::vec3& contactPoint, float& penDepth, glm::vec3& normal){
	penDepth = size - sqrt((position[0] - parposition[0])*(position[0] - parposition[0]) + (position[1] - parposition[1])*(position[1] - parposition[1]) + (position[2] - parposition[2])*(position[2] - parposition[2]));
	if ( penDepth > 0) {
		normal = (parposition - position) / glm::length((parposition - position));
		contactPoint = normal*size;
		return true;
	}

	return false;
}