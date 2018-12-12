#include "Shader.h"
#include <iostream>

dn::Shader::Shader(const std::string &p_vertexSource, const std::string &p_fragmentSource)
	: _vertexSource(p_vertexSource), _fragmentSource(p_fragmentSource), _programId(0)
{

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
