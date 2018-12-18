#include "Shader.hpp"
#include "Application.hpp"
#include <fstream>
#include <sstream>

dn::Shader::Shader(const std::string &p_vertexShader, const std::string &p_fragmentShader, const bool &p_file)
	: _vertexSource(p_vertexShader), _fragmentSource(p_fragmentShader), _programId(0)
{
	if (p_file)
	{
		std::ifstream ofile;
		ofile.open(p_vertexShader);
		{
			std::stringstream strm;
			strm << ofile.rdbuf();
			this->_vertexSource = strm.str();
		}
		ofile.close();
		ofile.open(p_fragmentShader);
		{
			std::stringstream strm;
			strm << ofile.rdbuf();
			this->_fragmentSource = strm.str();
		}
		ofile.close();
	}
	dn::Application::addShader(this);
}

dn::Shader::~Shader()
{
	if (this->_programId)
		glDeleteProgram(this->_programId);
}

std::string dn::Shader::vertexSource() const { return (this->_vertexSource); }
std::string dn::Shader::fragmentSource() const { return (this->_fragmentSource); }

GLuint dn::Shader::programId() const { return (this->_programId); }
const char *dn::Shader::infoLog() const { return (this->_infoLog); }

GLint dn::Shader::getAttrib(const std::string &p_name)
{
	if (!this->_programId)
		return (-1);
	return (glGetAttribLocation(this->_programId, p_name.c_str()));
}

GLint dn::Shader::getUniform(const std::string &p_name)
{
	if (!this->_programId)
		return (-1);
	return (glGetUniformLocation(this->_programId, p_name.c_str()));
}

static GLuint compileShader(const char *p_source, const GLenum &p_type, int &p_status, char p_log[512])
{
	GLuint shaderId;

	shaderId = glCreateShader(p_type);
	glShaderSource(shaderId, 1, &p_source, nullptr);
	glCompileShader(shaderId);
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &p_status);
	if (!p_status)
	{
		glGetShaderInfoLog(shaderId, 512, nullptr, p_log);
		glDeleteShader(shaderId);
		return (0);
	}
	return (shaderId);
}

bool dn::Shader::compile()
{
	if (this->_programId)
		return true;

	GLuint vertexId, fragmentId;
	int status;

	if (!(vertexId = compileShader(this->_vertexSource.c_str(), GL_VERTEX_SHADER, status, this->_infoLog)))
		return (false);
	if (!(fragmentId = compileShader(this->_fragmentSource.c_str(), GL_FRAGMENT_SHADER, status, this->_infoLog)))
		return (false);
	this->_programId = glCreateProgram();
	glAttachShader(this->_programId, vertexId);
	glAttachShader(this->_programId, fragmentId);
	glLinkProgram(this->_programId);

	glDetachShader(this->_programId, vertexId);
	glDeleteShader(vertexId);
	glDetachShader(this->_programId, fragmentId);
	glDeleteShader(fragmentId);

	glGetProgramiv(this->_programId, GL_COMPILE_STATUS, &status);
	if (!status)
	{
		glGetProgramInfoLog(this->_programId, 512, nullptr, this->_infoLog);
		glDeleteProgram(this->_programId);
		return (false);
	}
	return (true);
}

void dn::Shader::use(const bool &p_use)
{
	if (this->_programId)
		glUseProgram(p_use ? this->_programId : 0);
}

static const char *g_vertexSource = GLSL(
	in vec3 position;
	in vec4 color;
	in vec2 tex;

	uniform mat4 transform;
	uniform mat4 viewProjection;

	out vec2 otex;
	out vec4 ocolor;
	void main()
	{
		gl_Position = viewProjection * transform * vec4(position, 1);
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
		color = ocolor;
	}
);

dn::Shader dn::Shader::defaultShader(g_vertexSource, g_fragmentSource, false);
