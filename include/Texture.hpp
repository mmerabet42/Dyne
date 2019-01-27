#ifndef DN_TEXTURE_HPP
# define DN_TEXTURE_HPP

# include <vector>
# include "ApplicationDependent.hpp"
# include "allgl.hpp"

namespace dn
{
	class Texture: public dn::ApplicationDependent
	{
	public:
		Texture(const std::string &p_path);
		~Texture();

		int width() const;
		int height() const;
		GLuint textureId() const;

		unsigned char *data() const;

		std::string path() const;
		void setPath(const std::string &p_path);

		void bind(const GLenum &p_unit = 0);
		void unbind();

		void create();
		void destroy();

		static unsigned char *load(const std::string &p_path, int &p_width, int &p_height);

	private:
		int _width;
		int _height;

		unsigned char *_data;

		GLuint _tex;

		std::string _path;
	};
}

#endif // DN_TEXTURE_HPP
