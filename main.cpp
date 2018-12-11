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
#include "Event.h"
int main()
{
	dn::Event<int, std::string> ev;

	dn::connect(ev, [&](int a, std::string b) {
		std::cout << "Hello : " << a << " " << b << std::endl;
	});

	ev.trigger(3, "Hello world");
	return (0);

	dn::Window *win = new dn::Window(600, 400, "loader");

	win->setClearColor(37, 44, 56);

	GLuint progId, vao, vbo[2];
	GLfloat vertices[] = {
		0, 0.5f,		1, 0, 1, 1,
		0.5f, -0.5f,	1, 1, 0, 1,
		-0.5f, -0.5f,	0, 0, 1, 1
	};
	GLuint indices[] = {
		0, 1, 2
	};

	dn::Application::setStartCb([&]() {
		progId = compileProgram(g_vertexSource, g_fragmentSource);
		if (progId == -1)
		{
			dn::Application::stop();
			return ;
		}

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(2, vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		GLint positionAttrib = glGetAttribLocation(progId, "position");
		GLint colorAttrib = glGetAttribLocation(progId, "color");

		glEnableVertexAttribArray(positionAttrib);
		glVertexAttribPointer(positionAttrib, 2, GL_FLOAT, false, 6 * sizeof(GLfloat), 0);
		glEnableVertexAttribArray(colorAttrib);
		glVertexAttribPointer(colorAttrib,
			4, GL_FLOAT, false,
			6 * sizeof(GLfloat),
			(void *)(2 * sizeof(GLfloat)));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glBindVertexArray(0);
	});
	dn::Application::setExitCb([&]() {
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(2, vbo);
		glDeleteProgram(progId);
	});

	win->setStartCb([](dn::Window *win) {
		glViewport(0, 0, win->framebufferWidth(), win->framebufferHeight());
	});
	win->setFramebufferSizeCb([](dn::Window *win, int w, int h) {
		glViewport(0, 0, w, h);
	});
	win->setUpdateCb([&](dn::Window *win) {

		if (win->getKey(DN_KEY_ESCAPE))
			dn::Application::stop();

		win->clear();
		glUseProgram(progId);
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);
		glUseProgram(0);
		
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
//	std::cout << "OK until here !" << std::endl;
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

	glGetProgramiv(progId, GL_LINK_STATUS, &status);
	if (!status)
	{
		glGetProgramInfoLog(progId, 512, nullptr, errlog);
		std::cout << "Program linking error: " << errlog << std::endl;
		return (-1);
	}

	// Deleting the shaders as they are not needed anymore
	glDeleteShader(vertexId);
	glDeleteShader(fragmentId);

	// After succesfully compiling the shaders and linking the program,
	// we return the id.
	return (progId);
}
