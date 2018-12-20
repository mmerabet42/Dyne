#include "Application.hpp"
#include "Shader.hpp"

int dn::Application::compileShaders()
{
	for (size_t i = 0; i < dn::Application::_shaders.size(); ++i)
	{
		if (!dn::Application::_shaders[i]->compile())
		{
			dn::Application::terminate(
				std::string("Shader compilation error: ") + dn::Application::_shaders[i]->infoLog(),
				DN_SHADER_FAIL);
			dn::Application::_shaders.clear();
			return (DN_SHADER_FAIL);
		}
	}
	dn::Application::_shaders.clear();
	return (DN_OK);
}

void dn::Application::addShader(dn::Shader *p_shader)
{
	if (dn::Application::_running)
	{
		if (!p_shader->compile())
			dn::Application::terminate(
				std::string("Shader compilation error: ") + p_shader->infoLog(),
				DN_SHADER_FAIL);
	}
	else
		dn::Application::_shaders.push_back(p_shader);
}
