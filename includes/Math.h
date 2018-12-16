#ifndef MATH_H
# define MATH_H

# include "glm/vec3.hpp"
# define SPRING_CONSTANT 0.1f

namespace dn { namespace math
{
	float smoothDamp(const float &current, const float &target, float &vel, const float &smoothDamp);

	glm::vec3 smoothDamp(const glm::vec3 &current,
			const glm::vec3 &target,
			glm::vec3 &vel,
			const float &smoothDamp);

}}

#endif // MATH_H
