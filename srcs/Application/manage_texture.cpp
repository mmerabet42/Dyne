#include "Application.hpp"
#include "Texture.hpp"

void dn::Application::addTexture(dn::Texture *p_texture)
{
	if (dn::Application::_running)
		p_texture->create();
	else
		dn::Application::_textures.push_back(p_texture);
}

void dn::Application::createTextures()
{
	for (size_t i = 0; i < dn::Application::_textures.size(); ++i)
		dn::Application::_textures[i]->create();
	dn::Application::_textures.clear();
}
