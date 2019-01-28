#ifndef DN_VERTEX_HPP
# define DN_VERTEX_HPP

# include "dn/allgl.hpp"

namespace dn
{
	struct Vertex
	{
		GLfloat position[3];
		GLfloat color[4];
		GLfloat tex[2];
		GLfloat normal[3];
	};
}

#endif // DN_VERTEX_HPP
