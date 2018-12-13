#ifndef MESH_H
# define MESH_H

# include "glm/glm.hpp"
# include "GL/glew.h"
# include "Shader.h"
# include "Shape.h"

namespace dn
{
	class Model
	{
	public:
		Model(const dn::Shape &p_shape, dn::Shader *p_shader = &dn::Shader::defaultShader);
		~Model();

		const dn::Shape &shape() const;
		void setShape(const dn::Shape &p_shape);

		const dn::Shader *shader() const;
		void setShader(dn::Shader *p_shader);

		glm::vec3 position() const;
		glm::vec3 &position();

		glm::vec3 rotation() const;
		glm::vec3 &rotation();

		glm::vec3 scale() const;
		glm::vec3 &scale();

		dn::Model *parent() const;
		void setParent(dn::Model *p_parent);

		const glm::mat4 &transform();

		void create();
		void draw(const GLenum &p_mode);

	private:

		dn::Model *_parent;

		dn::Shape _shape;
		dn::Shader *_shader;
		GLuint _vao;
		GLuint _vbos[2];

		glm::vec3 _position;
		glm::vec3 _rotation;
		glm::vec3 _scale;

		glm::mat4 _positionMat;
		glm::mat4 _rotationMat;
		glm::mat4 _scaleMat;

		glm::mat4 _transform;

		bool _positionMod;
		bool _rotationMod;
		bool _scaleMod;
		bool _change;

		bool change() const;
	};
}

#endif
