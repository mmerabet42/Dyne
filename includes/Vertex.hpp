#ifndef VERTEX_HPP
# define VERTEX_HPP

# include "allgl.hpp"

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

#endif // VERTEX_HPP
