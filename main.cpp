#include <iostream>

#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"

#include "Window.h"
#include "Application.h"
#include "Shader.h"
#include "Vertex.h"

#define GLSL(CODE) "#version 330 core\n" #CODE

static const char *g_vertexSource = GLSL(
	in vec2 position;
	in vec4 color;

	uniform mat4 transform;

	out vec4 ocolor;

	void main()
	{
		gl_Position =  vec4(position, 0, 1);
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

void closeEscape(dn::Window *win, int k, int a, int m) { if (k == DN_KEY_ESCAPE) win->close(); }
void closeApplication(dn::Window *win, int k, int a, int m) { if (k == DN_KEY_ESCAPE) dn::app::stop(); }

// Compiles a shader program, specifying the vertex source and the fragment source.
int compileProgram(const char *p_vertex, const char *p_fragment);

int main()
{
	dn::Window *win = new dn::Window(600, 400, "First");
	dn::Shader *shader = new dn::Shader(g_vertexSource, g_fragmentSource);

	win->keyEvent(closeApplication);
	win->setClearColor(37, 44, 56);

	GLuint vao, vbo[2];
	dn::Vertex vertices[] = {
		{{-0.5f, 0.5f},	{1.f, 0.f, 1.f}},
		{{0.5f, 0.5f},	{1.f, 1.f, 0.f}},
		{{0.5f, -0.5f},	{0.f, 0.f, 1.f}},
		{{-0.5f, -0.5f},{0.f, 0.f, 1.f}}
	};
	GLuint indices[] = {
		1, 0, 2, 3
	};
	
	win->startEvent.addListener([&](dn::Window *win) {
		if (!shader->compile())
		{
			std::cout << "Shader compilation error: " << shader->infoLog() << std::endl;
			dn::Application::stop();
			return ;
		}

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(2, vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		GLint positionAttrib = shader->getAttrib("position");
		GLint colorAttrib = shader->getAttrib("color");

		glEnableVertexAttribArray(positionAttrib);
		glVertexAttribPointer(positionAttrib, 2, GL_FLOAT, false, sizeof(dn::Vertex), 0);
		glEnableVertexAttribArray(colorAttrib);
		glVertexAttribPointer(colorAttrib,
			4, GL_FLOAT, false,
			sizeof(dn::Vertex),
			(void *)(2 * sizeof(GLfloat)));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glBindVertexArray(0);
	});
	win->closeEvent.addListener([&](dn::Window *win) {
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(2, vbo);
		delete shader;
	});

	win->startEvent.addListener([](dn::Window *win) {
		glViewport(0, 0, win->framebufferWidth(), win->framebufferHeight());
	});
	win->framebufferSizeEvent.addListener([](dn::Window *win, int w, int h) {
		glViewport(0, 0, w, h);
	});

	glm::vec3 position(0.f, 0.f, 0.f);
	glm::quat rotation(glm::vec3(0.f, 0.f, 0.f));
	glm::vec3 scale(1.f, 1.f, 1.f);

	win->updateEvent.addListener([&](dn::Window *win) {
		win->clear();

/*
		glm::mat4 transform = glm::translate(position)
							* glm::toMat4(rotation);
							* glm::scale(scale);
*/

		shader->use();
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);
		shader->use(false);
	});

	dn::Application::setFlag(DN_FREEWINDOWS, true);
	dn::Application::run();
	return (0);
}
/*
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
}*/
