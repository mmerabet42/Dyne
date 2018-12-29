#include "Shader.hpp"

static const char *g_vertexSource = GLSL(
	in vec3 position;
	in vec4 color;
	in vec2 tex;

	uniform mat4 transform;

	out vec2 otex;
	out vec4 ocolor;
	void main()
	{
		gl_Position = transform * vec4(position, 1);
		ocolor = color;
		otex = tex;
	}
);

static const char *g_fragmentSource = GLSL(
	in vec4 ocolor;
	in vec2 otex;

	const int DN_VERTEX_COLOR = (1 << 0);
	const int DN_TEXTURE_COLOR = (1 << 1);
	const int DN_MESH_COLOR = (1 << 2);

	uniform sampler2D unit;
	uniform int renderMode;
	uniform vec4 meshColor;

	out vec4 color;
	void main()
	{
		vec4 fragColor;

		if (bool(renderMode & DN_VERTEX_COLOR))
			fragColor = ocolor;
		if (bool(renderMode & DN_TEXTURE_COLOR))
		{
			if (bool(renderMode & DN_VERTEX_COLOR))
				fragColor = fragColor * texture(unit, otex);
			else
				fragColor = texture(unit, otex);
		}
		if (bool(renderMode & DN_MESH_COLOR))
		{
			if (bool(renderMode & (DN_VERTEX_COLOR | DN_TEXTURE_COLOR)))
				fragColor = fragColor * meshColor;
			else
				fragColor = meshColor;
		}

		color = fragColor;
	}
);

dn::Shader dn::Shader::defaultShader(g_vertexSource, g_fragmentSource, false);
