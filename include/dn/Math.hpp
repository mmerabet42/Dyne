#ifndef DN_MATH_HPP
# define DN_MATH_HPP

# include "glm/vec3.hpp"
# define SPRING_CONSTANT 0.1f

# include "Matrix.hpp"

namespace dn { namespace math
{
	// Smooth the transition of `current' to `target' according to `smoothDamp'
	float smoothDamp(const float &current, const float &target, float &vel, const float &smoothDamp);

	glm::vec3 smoothDamp(const glm::vec3 &current,
			const glm::vec3 &target,
			glm::vec3 &vel,
			const float &smoothDamp);

	// Generate a random floating point number between two other floating point
	float random(const float &p_min, const float &p_max);
	glm::vec3 randomVector(const float &p_min, const float &p_max);

	dn::Matrix<4, 4, float> translate(dn::Vector<3, float> &p_v);
}}

#endif // DN_MATH_HPP
