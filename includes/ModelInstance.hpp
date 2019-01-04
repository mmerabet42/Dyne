#ifndef MODELINSTANCE_HPP
# define MODELINSTANCE_HPP

namespace dn
{
	class Shader;
	class Model;

	class ModelInstance
	{
	public:
		ModelInstance(dn::Shader *p_shader, dn::Model *p_model);

		void bind();

		const dn::Shader *shader() const;
		const dn::Model *model() const;

	private:
		dn::Shader *_shader;
		dn::Model *_model;
	};
}

#endif // MODELINSTANCE_HPP
