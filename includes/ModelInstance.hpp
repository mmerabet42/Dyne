#ifndef MODELINSTANCE_HPP
# define MODELINSTANCE_HPP

# include "ApplicationDependent.hpp"
# include "allgl.hpp"
# include "glm/matrix.hpp"
# include "glm/vec4.hpp"

namespace dn
{
	class Shader;
	class Model;

	struct InstanceData
	{
		glm::mat4 transform;
		int renderMode;
		glm::vec4 meshColor;
	};

	class ModelInstance: public dn::ApplicationDependent
	{
	public:
		ModelInstance(dn::Shader *p_shader, dn::Model *p_model);
		~ModelInstance();

		void bind();
		void bindInstanceVb();

		void create();
		void destroy();

		const dn::Shader *shader() const;
		const dn::Model *model() const;

	private:
		dn::Shader *_shader;
		dn::Model *_model;

		GLuint _vao;

		enum { VERTEX_VB, INDEX_VB, INSTANCE_VB, VB_SIZE };
		GLuint _vbos[VB_SIZE];
	};
}

#endif // MODELINSTANCE_HPP
