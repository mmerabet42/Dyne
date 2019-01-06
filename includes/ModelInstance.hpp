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

		GLuint instanceVb() const;

	private:
		dn::Shader *_shader;
		dn::Model *_model;

		GLuint _vao;

		enum { VERTEX_VB, INDEX_VB, INSTANCE_VB, VB_SIZE };
		GLuint _vbos[VB_SIZE];
	};
}

#endif // MODELINSTANCE_HPP
