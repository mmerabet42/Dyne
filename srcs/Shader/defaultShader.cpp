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

	uniform sampler2D unit;

	out vec4 color;
	void main()
	{
		color = texture(unit, otex) * ocolor;
	}
);

dn::Shader dn::Shader::defaultShader(g_vertexSource, g_fragmentSource, false);
