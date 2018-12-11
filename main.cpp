#include <iostream>

#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
extern "C" {
#include "ft_lexiq.h"
#include "ft_printf.h"
}

#define DN_APPLICATION_FREEWINDOWS
#include "Window.h"
#include "Application.h"

#define GLSL(CODE) "#version 330 core\n" #CODE

static const char *g_vertexSource = GLSL(
	in vec2 position;
	in vec4 color;
	out vec4 ocolor;
	void main()
	{
		gl_Position = vec4(position, 0, 1);
		ocolor = color;
	}
);

static const char *g_fragmentSource = GLSL(
	in vec4 ocolor;
	out vec4 color;
	void main()
	{
		color = ocolor;
	}
);

// Compiles a shader program, specifying the vertex source and the fragment source.
int compileProgram(const char *p_vertex, const char *p_fragment);

int main()
{
	dn::Window *win = new dn::Window(600, 400, "My Window");

//	GLuint progId = compileProgram(g_vertexShader, g_fragmentSource);
	GLuint progId = -1;
	if (progId == -1)
		return (dn::Application::terminate());

	win->setUpdateCb([](dn::Window *win) {
		win->clear();

		if (win->getKey(DN_KEY_ESCAPE))
			dn::Application::stop();
	});

	return (dn::Application::run());
}

// Compiles a shader program
int compileProgram(const char *p_vertex, const char *p_fragment)
{
	GLuint progId, vertexId, fragmentId;
	GLint status;
	char errlog[512];

	// Creating the vertex shader
	vertexId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexId, 1, &p_vertex, nullptr);
	glCompileShader(vertexId);
	// If a compilation error occured
	glGetShaderiv(vertexId, GL_COMPILE_STATUS, &status);
	if (!status)
	{
		glGetShaderInfoLog(vertexId, 512, nullptr, errlog);
		std::cout << "Shader compilation error: " << errlog << std::endl;
		return (-1);
	}

	// Creating the fragment shader
	fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentId, 1, &p_fragment, nullptr);
	glCompileShader(fragmentId);
	glGetShaderiv(fragmentId, GL_COMPILE_STATUS, &status);
	if (!status)
	{
		glGetShaderInfoLog(fragmentId, 512, nullptr, errlog);
		std::cout << "Shader compilation error: " << errlog << std::endl;
		return (-1);
	}

	// Creating the program
	progId = glCreateProgram();
	// Attaching the shaders to the program
	glAttachShader(progId, vertexId);
	glAttachShader(progId, fragmentId);
	// And finally linking the program
	glLinkProgram(progId);
	// Returning the id of the program
	return (progId);
}
