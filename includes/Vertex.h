#ifndef VERTEX_H
# define VERTEX_H

# include "Color.h"
# include "GL/glew.h"

namespace dn
{
	struct Vertex
	{
		GLfloat position[3];
		GLfloat color[4];
	};
}

#endif // VERTEX_H
