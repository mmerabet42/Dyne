#include "Math.hpp"
#include <random>

float dn::math::random(const float &p_min, const float &p_max)
{
	static std::default_random_engine eng;
	std::uniform_real_distribution<float> dist(p_min, p_max);
	return (dist(eng));
}
