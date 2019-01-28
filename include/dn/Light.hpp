#ifndef DN_LIGHT_HPP
# define DN_LIGHT_HPP

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

#endif // DN_LIGHT_HPP
