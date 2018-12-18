#ifndef TEXTURE_HPP
# define TEXTURE_HPP

# include <vector>
# include "allgl.hpp"

namespace dn
{
	class Texture
	{
	public:
		Texture(const std::string &p_path);

		int width() const;
		int height() const;
		GLuint textureId() const;

		unsigned char *data() const;

		std::string path() const;
		void setPath(const std::string &p_path);

		void bind(const GLenum &p_unit = 0);
		void unbind();

		void create();

		static unsigned char *load(const std::string &p_path, int &p_width, int &p_height);
		static void createTextures();

	private:
		int _width;
		int _height;

		unsigned char *_data;

		GLuint _tex;

		std::string _path;

		static std::vector<dn::Texture *> _textures;
	};
}

#endif // TEXTURE_HPP
