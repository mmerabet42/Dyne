#ifndef MESHRENDERER_HPP
# define MESHRENDERER_HPP

# include "Component.hpp"
# include "Shader.hpp"
# include "Model.hpp"
# include "glm/vec4.hpp"

namespace dn
{
	class Texture;

	class MeshRenderer: public dn::Component
	{
	public:
		MeshRenderer(dn::Model *p_model = nullptr, dn::Shader *p_shader = &dn::Shader::defaultShader);
		MeshRenderer(const dn::Model &p_model, dn::Shader *p_shader = &dn::Shader::defaultShader);
		~MeshRenderer();

		dn::Model *model() const;
		void setModel(dn::Model *p_model);
		void setModel(const dn::Model &p_model);

		dn::Shader *shader() const;
		void setShader(dn::Shader *p_shader);

		dn::Texture *texture() const;
		void setTexture(dn::Texture *p_texture);

		glm::vec4 color() const;
		glm::vec4 &color();
		void setColor(const glm::vec4 &p_color);
		void setColor(const float &p_r, const float &p_g, const float &p_b, const float &p_a = 1.f);

		void setRenderMode(const int &p_mode);

		void start();
		void update();

	private:
		dn::Model *_model;
		dn::Shader *_shader;

		// Different rendering modes
		dn::Texture *_texture;
		glm::vec4 _color;
		int _renderMode;

		GLuint _vao;
		GLuint _vbos[2];

		bool _modelAllocated;
	};
}

#endif // MESHRENDERER_HPP
