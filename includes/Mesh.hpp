#ifndef DN_MESH_HPP
# define DN_MESH_HPP

# include "Component.hpp"
# include "Shader.hpp"
# include "glm/vec4.hpp"

namespace dn
{
	class Model;
	class Texture;

	class Mesh: public dn::Component
	{
	public:
		Mesh(dn::Model *p_model, dn::Shader *p_shader = &dn::Shader::defaultShader);

		dn::Model *model() const;
		void setModel(dn::Model *p_model);

		dn::Shader *shader() const;
		void setShader(dn::Shader *p_shader);

		dn::Texture *texture() const;
		void setTexture(dn::Texture *p_texture);

		glm::vec4 color() const;
		glm::vec4 &color();
		void setColor(const glm::vec4 &p_color);
		void setColor(const float &p_r, const float &p_g, const float &p_b, const float &p_a = 1.f);

		int renderMode() const;
		void setRenderMode(const int &p_mode);
	private:
		dn::Model *_model;
		dn::Shader *_shader;

		dn::Texture *_texture;
		glm::vec4 _color;
		int _renderMode;
	};
}

#endif // DN_MESH_HPP
