#include "Shader.hpp"

static const char *g_vertexSource = GLSL(
	in vec3 position;
	in vec4 color;
	in vec2 tex;
	in vec3 normal;

	uniform mat4 transform;
	uniform mat4 viewprojection;
	uniform vec3 lightPosition;

	out vec2 otex;
	out vec4 ocolor;
	out vec3 onormal;
	out vec3 lightDir;

	void main()
	{
		vec4 worldPosition = transform * vec4(position, 1.0);

		gl_Position = viewprojection * worldPosition;
		ocolor = color;
		otex = tex;
		onormal = normalize((transform * vec4(normal, 0.0)).xyz);
		lightDir = normalize(lightPosition - worldPosition.xyz);
	}
);

static const char *g_fragmentSource = GLSL(
	in vec4 ocolor;
	in vec2 otex;
	in vec3 onormal;
	in vec3 lightDir;

	const int DN_VERTEX_COLOR	= (1 << 0);
	const int DN_TEXTURE_COLOR	= (1 << 1);
	const int DN_MESH_COLOR		= (1 << 2);
	const int DN_LIGHT_COLOR	= (1 << 3);

	uniform sampler2D unit;
	uniform int renderMode;
	uniform vec4 meshColor;
	uniform vec3 lightColor;

	out vec4 color;
	void main()
	{
		vec4 usedColor;

		if (bool(renderMode & DN_VERTEX_COLOR))
			usedColor = ocolor;
		if (bool(renderMode & DN_TEXTURE_COLOR))
		{
			if (bool(renderMode & DN_VERTEX_COLOR))
				usedColor = usedColor * texture(unit, otex);
			else
				usedColor = texture(unit, otex);
		}
		if (bool(renderMode & DN_MESH_COLOR))
		{
			if (bool(renderMode & (DN_VERTEX_COLOR | DN_TEXTURE_COLOR)))
				usedColor = usedColor * meshColor;
			else
				usedColor = meshColor;
		}
		if (bool(renderMode & DN_LIGHT_COLOR))
		{
			vec3 diffuse = max(dot(onormal, lightDir), 0.0) * lightColor;
			usedColor = vec4(diffuse, 1.0) * usedColor;
		}
		color = usedColor;
	}
);

dn::Shader dn::Shader::defaultShader(g_vertexSource, g_fragmentSource, false);
