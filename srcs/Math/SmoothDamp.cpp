#include "Math.hpp"
#include <cmath>

float dn::math::smoothDamp(const float &current, const float &target, float &vel, const float &smoothDamp)
{
	return (current + ((vel += (((target - current) * SPRING_CONSTANT) + (-vel * 2 * std::sqrt(SPRING_CONSTANT))) * smoothDamp) * smoothDamp));
}

glm::vec3 dn::math::smoothDamp(
		const glm::vec3 &current,
		const glm::vec3 &target,
		glm::vec3 &vel,
		const float &smoothDamp)
{
	return glm::vec3(
		dn::math::smoothDamp(current.x, target.x, vel.x, smoothDamp),
		dn::math::smoothDamp(current.y, target.y, vel.y, smoothDamp),
		dn::math::smoothDamp(current.z, target.z, vel.z, smoothDamp)
	);
}
