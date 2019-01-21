#ifndef LIGHT_HPP
# define LIGHT_HPP

# include "glm/vec3.hpp"

namespace dn
{
	class Light
	{
	public:
		static glm::vec3 lightPosition;
		static glm::vec3 lightColor;
	};
}

#endif // LIGHT_HPP
