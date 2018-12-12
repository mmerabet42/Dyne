#ifndef SHADER_H
# define SHADER_H

# include "GL/glew.h"
# include <string>

namespace dn
{
	class Shader
	{
	public:
		Shader(const std::string &p_vertexSource, const std::string &p_fragmentSource);
		~Shader();

		bool compile();

		std::string vertexSource() const;
		std::string fragmentSource() const;
		
		GLuint programId() const;
		const char *infoLog() const;

		GLint getAttrib(const std::string &p_name);
		GLint getUniform(const std::string &p_name);

		void use(const bool &p_use = true);

	private:
		char _infoLog[512];
		GLuint _programId;
		std::string _vertexSource;
		std::string _fragmentSource;
	};
}

#endif // SHADER_H
