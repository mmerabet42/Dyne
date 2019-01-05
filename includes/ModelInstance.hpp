#ifndef MODELINSTANCE_HPP
# define MODELINSTANCE_HPP

# include "ApplicationDependent.hpp"
# include "allgl.hpp"

namespace dn
{
	class Shader;
	class Model;

	class ModelInstance: public dn::ApplicationDependent
	{
	public:
		ModelInstance(dn::Shader *p_shader, dn::Model *p_model);
		~ModelInstance();

		void bind();

		void create();
		void destroy();

		const dn::Shader *shader() const;
		const dn::Model *model() const;

	private:
		dn::Shader *_shader;
		dn::Model *_model;

		GLuint _vao;
		GLuint _vbos[2];
	};
}

#endif // MODELINSTANCE_HPP
