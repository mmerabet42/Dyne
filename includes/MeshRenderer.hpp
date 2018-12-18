#ifndef MESHRENDERER_HPP
# define MESHRENDERER_HPP

# include "Component.hpp"
# include "Shader.hpp"
# include "Model.hpp"

namespace dn
{
	class Texture;

	class MeshRenderer: public dn::Component
	{
	public:
		MeshRenderer(dn::Model *p_model = nullptr, dn::Shader *p_shader = &dn::Shader::defaultShader);
		~MeshRenderer();

		dn::Model *model() const;
		void setModel(dn::Model *p_model);

		dn::Shader *shader() const;
		void setShader(dn::Shader *p_shader);

		dn::Texture *texture() const;
		void setTexture(dn::Texture *p_texture);

		void start();
		void update();

	private:
		dn::Model *_model;
		dn::Shader *_shader;

		dn::Texture *_texture;

		GLuint _vao;
		GLuint _vbos[2];
	};
}

#endif // MESHRENDERER_HPP
