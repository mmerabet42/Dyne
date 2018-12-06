#include <iostream>

#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
extern "C" {
#include "ft_lexiq.h"
}
#define GLSL(CODE) "#version 330 core\n" #CODE

int CloseApp(const std::string &msg = "ERROR", const int &code = -1, const bool &terminateGlfw = true);

const char *vertexSource = GLSL(
	in vec2 position;
	in vec4 color;

	out vec4 ocolor;

	void main()
	{
		gl_Position = vec4(position, 0, 1);
		ocolor = color;
	}
);

const char *fragmentSource = GLSL(
	in vec4 ocolor;

	out vec4 color;

	void main()
	{
		color = ocolor;
	}
);

void ResizeWindowCallBack(GLFWwindow *window, int width, int height);

int main()
{
	int	n = ft_lexiq(0, "*[@upper]", "HELLO");
	std::cout << "Match: " << n << std::endl;
	if (!glfwInit())
		CloseApp("ERROR : GLFW failed to init");
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
	glfwWindowHint(GLFW_SAMPLES, 8);

	GLFWwindow *window = glfwCreateWindow(600, 600, "Hello world", nullptr, nullptr);
	if (!window)
		CloseApp("ERROR : The window was not created.");
	
	glfwMakeContextCurrent(window);

	glfwSetWindowSizeCallback(window, ResizeWindowCallBack);

	glewExperimental = true;
	if (glewInit() != GLEW_OK)
		CloseApp("ERROR : GLEW failed to init");

	glViewport(0, 0, 600, 600);

	GLint status;
	char log[512];

	GLuint vertexId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexId, 1, &vertexSource, nullptr);
	glCompileShader(vertexId);
	
	glGetShaderiv(vertexId, GL_COMPILE_STATUS, &status);
	if (!status)
	{
		glGetShaderInfoLog(vertexId, 512, nullptr, log);
		CloseApp("ERROR VERTEX SHADER COMPILATION : " + std::string(log));
	}

	GLuint fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentId, 1, &fragmentSource, nullptr);
	glCompileShader(fragmentId);

	glGetShaderiv(fragmentId, GL_COMPILE_STATUS, &status);
	if (!status)
	{
		glGetShaderInfoLog(fragmentId, 512, nullptr, log);
		CloseApp("ERROR FRAGMENT SHADER COMPILATION : " + std::string(log));
	}

	GLuint progId = glCreateProgram();
	glAttachShader(progId, vertexId);
	glAttachShader(progId, fragmentId);
	glLinkProgram(progId);

	GLfloat vertices[] = {
		0, 0.5f,	0.5f, 1, 1, 1,
		0.5f, 0,	1, 1, 0.5f, 1,
		-0.5f, 0,	1, 0.5f, 1, 1
	};
	GLuint indices[] = {
		0, 1, 2
	};

	GLuint vao, vbo[2];
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(2, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLint positionAttrib = glGetAttribLocation(progId, "position");
	glEnableVertexAttribArray(positionAttrib);
	glVertexAttribPointer(positionAttrib, 2, GL_FLOAT, false, 6 * sizeof(GLfloat), 0);

	GLint colorAttrib = glGetAttribLocation(progId, "color");
	glEnableVertexAttribArray(colorAttrib);
	glVertexAttribPointer(colorAttrib, 4, GL_FLOAT, false, 6 * sizeof(GLfloat), (void *)(2 * sizeof(GLfloat)));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);

	glUseProgram(progId);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		if (glfwGetKey(window, GLFW_KEY_ESCAPE))
			break;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		{
			glBindVertexArray(vao);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
			glBindVertexArray(0);
		}

		glfwSwapBuffers(window);
	}

	return (CloseApp("The app terminated successfully !", 0));
}

int CloseApp(const std::string &msg, const int &code, const bool &terminateGlfw)
{
	if (terminateGlfw)
		glfwTerminate();
	std::cout << msg << std::endl;
	exit(code);
}

void ResizeWindowCallBack(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}
