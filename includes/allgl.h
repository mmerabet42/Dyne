#ifndef ALLGL_H
# define ALLGL_H

# include "GL/glew.h"
# include "GLFW/glfw3.h"

# include <iostream>

float mSmoothDamp(const float &current, const float &target, float &vel, const float &smoothDamp)
{
	return (current + ((vel += (((target - current) * SPRING_CONSTANT) + (-vel * 2 * sqrt(SPRING_CONSTANT))) * smoothDamp) * smoothDamp));
}

glm::vec3 mSmoothDamp(const glm::vec3 &current, const glm::vec3 &target, glm::vec3 &vel, const float &smoothDamp)
{
	return glm::vec3(
		mSmoothDamp(current.x, target.x, vel.x, smoothDamp),
		mSmoothDamp(current.y, target.y, vel.y, smoothDamp),
		mSmoothDamp(current.z, target.z, vel.z, smoothDamp)
	);
}

#endif // ALLGL_H
