#ifndef MESHRENDERER_HPP
# define MESHRENDERER_HPP

# include "Component.hpp"
# include "Shader.hpp"
# include "Model.hpp"
# include "glm/vec4.hpp"
# include "glm/vec3.hpp"

namespace dn
{
	class Texture;
	class Transform;

	class MeshRenderer: public dn::Component
	{
	public:
		MeshRenderer(dn::Model *p_model, dn::Shader *p_shader = &dn::Shader::defaultShader);

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

		void start();
		void update();

		dn::Transform *transform() const;
	private:
		dn::Model *_model;
		dn::Shader *_shader;

		dn::Transform *_transform;

		// Different rendering modes
		dn::Texture *_texture;
		glm::vec4 _color;
		int _renderMode;
	};

	class MeshData: public dn::ComponentData
	{
	public:
		MeshData(dn::Model *p_model, dn::Shader *p_shader = &dn::Shader::defaultShader);

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

#endif // MESHRENDERER_HPP
