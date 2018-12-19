#include "Texture.hpp"
#include "Application.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

dn::Texture::Texture(const std::string &p_path)
	: _path(p_path), _tex(0)
{
	this->_data = dn::Texture::load(p_path, this->_width, this->_height);
	if (dn::Application::running())
		this->create();
}

void dn::Texture::create()
{
	if (!dn::Application::running() || this->_tex)
		return ;
	glGenTextures(1, &this->_tex);
	glBindTexture(GL_TEXTURE_2D, this->_tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->_width, this->_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->_data);

	glBindTexture(GL_TEXTURE_2D, 0);
}


int dn::Texture::width() const { return (this->_width); }
int dn::Texture::height() const { return (this->_height); }
GLuint dn::Texture::textureId() const { return (this->_tex); }
unsigned char *dn::Texture::data() const { return (this->_data); }

std::string dn::Texture::path() const { return (this->_path); }
void dn::Texture::setPath(const std::string &p_path)
{
	this->_path = p_path;
}

void dn::Texture::bind(const GLenum &p_unit)
{
	if (!dn::Application::running())
		return ;
	glActiveTexture(GL_TEXTURE0 + p_unit);
	glBindTexture(GL_TEXTURE_2D, this->_tex);
}

void dn::Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned char *dn::Texture::load(const std::string &p_path, int &p_width, int &p_height)
{
	int comp;
	return (stbi_load(p_path.c_str(), &p_width, &p_height, &comp, 4));
}
