#ifndef DN_SHADER_HPP
# define DN_SHADER_HPP

# include <string>
# include <vector>
# include <map>
# include "ApplicationDependent.hpp"
# include "allgl.hpp"

# define GLSL(CODE) "#version 330 core\n" #CODE

namespace dn
{
	class Shader: public dn::ApplicationDependent
	{
	public:
		Shader(const std::string &p_vertexShader, const std::string &p_fragmentShader, const bool &p_files = true);
		~Shader();

		void create();
		void destroy();

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

		std::map<std::string, GLint> _attribs;
		std::map<std::string, GLint> _uniforms;
	};
}

#endif // DN_SHADER_HPP
