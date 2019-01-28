#include "dn/Shader.hpp"
#include "dn/Application.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>

dn::Shader::Shader(const std::string &p_vertexShader, const std::string &p_fragmentShader, const bool &p_file)
	: ApplicationDependent(), _vertexSource(p_vertexShader), _fragmentSource(p_fragmentShader), _programId(0)
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
	dn::Application::addDependent(this);
}

dn::Shader::~Shader()
{
	dn::Application::destroyDependent(this);
}

std::string dn::Shader::vertexSource() const { return (this->_vertexSource); }
std::string dn::Shader::fragmentSource() const { return (this->_fragmentSource); }

GLuint dn::Shader::programId() const { return (this->_programId); }
const char *dn::Shader::infoLog() const { return (this->_infoLog); }

GLint dn::Shader::getAttrib(const std::string &p_name)
{
	if (!this->_programId)
		return (-1);
	std::map<std::string, GLint>::iterator it = this->_attribs.find(p_name);
	if (it != this->_attribs.end())
		return (it->second);
	GLint v = glGetAttribLocation(this->_programId, p_name.c_str());
	this->_attribs.insert(std::make_pair(p_name, v));
	return (v);
}

GLint dn::Shader::getUniform(const std::string &p_name)
{
	if (!this->_programId)
		return (-1);
	std::map<std::string, GLint>::iterator it = this->_uniforms.find(p_name);
	if (it != this->_uniforms.end())
		return (it->second);
	GLint v = glGetUniformLocation(this->_programId, p_name.c_str());
	this->_uniforms.insert(std::make_pair(p_name, v));
	return (v);
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

void dn::Shader::create()
{
	GLuint vertexId, fragmentId;
	int status;

	if (!(vertexId = compileShader(this->_vertexSource.c_str(), GL_VERTEX_SHADER, status, this->_infoLog)))
	{
		// for debug only, they'll be removed
		std::cout << this->_infoLog;
		return ;
	}
	if (!(fragmentId = compileShader(this->_fragmentSource.c_str(), GL_FRAGMENT_SHADER, status, this->_infoLog)))
	{
		// for debug only, they'll be removed
		std::cout << this->_infoLog;
		return ;
	}
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
		std::cout << this->_infoLog;
		glDeleteProgram(this->_programId);
	}
}

void dn::Shader::destroy()
{
	if (this->_programId)
		glDeleteProgram(this->_programId);
}

void dn::Shader::use(const bool &p_use)
{
	if (this->_programId)
		glUseProgram(p_use ? this->_programId : 0);
}
