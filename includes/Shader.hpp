#ifndef SHADER_HPP
# define SHADER_HPP

# include <string>
# include <vector>
# include "allgl.hpp"

# define GLSL(CODE) "#version 330 core\n" #CODE

namespace dn
{
	class Application;

	class Shader
	{
	public:
		Shader(const std::string &p_vertexShader, const std::string &p_fragmentShader, const bool &p_files = true);
		~Shader();

		bool compile();

		std::string vertexSource() const;
		std::string fragmentSource() const;
		
		GLuint programId() const;
		const char *infoLog() const;

		GLint getAttrib(const std::string &p_name);
		GLint getUniform(const std::string &p_name);

		void use(const bool &p_use = true);

		static dn::Shader defaultShader;

	private:
		char _infoLog[512];
		GLuint _programId;
		std::string _vertexSource;
		std::string _fragmentSource;
	};
}

#endif // SHADER_HPP
