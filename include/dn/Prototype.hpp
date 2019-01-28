#ifndef PROTOTYPE_HPP
# define PROTOTYPE_HPP

# include "glm/glm.hpp"
# include "dn/Shader.hpp"
# include "dn/Model.hpp"

namespace dn
{
	class Prototype
	{
	public:
		Prototype(const dn::Model &p_model, dn::Shader *p_shader = &dn::Shader::defaultShader);
		~Prototype();

		const dn::Model &model() const;
		void setModel(const dn::Model &p_model);

		const dn::Shader *shader() const;
		void setShader(dn::Shader *p_shader);

		glm::vec3 position() const;
		glm::vec3 &position();

		glm::vec3 rotation() const;
		glm::vec3 &rotation();

		glm::vec3 scale() const;
		glm::vec3 &scale();

		dn::Prototype *parent() const;
		void setParent(dn::Prototype *p_parent);

		const glm::mat4 &transform();

		void create();
		void draw(const GLenum &p_mode = -1);

	private:

		dn::Prototype *_parent;

		dn::Model _model;
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

	// Camera
	public:

		static const float &camFov();
		static void setCamFov(const float &p_fov);

		static const float &camNear();
		static void setCamNear(const float &p_near);

		static const float &camFar();
		static void setCamFar(const float &p_far);

		static const float &camAspectRatio();
		static void setCamAspectRatio(const float &p_aspectRatio);

		static const glm::vec3 &camPosition();
		static glm::vec3 &camPositionc();

		static const glm::vec3 &camRotation();
		static glm::vec3 &camRotationc();

		static glm::vec3 camForward();
		static glm::vec3 camUp();

		static const glm::mat4 &camViewProjection();

	private:
		static float _fov;
		static float _far;
		static float _near;
		static float _aspectRatio;

		static glm::vec3 _camPosition;
		static glm::vec3 _camRotation;

		static bool _viewMod;
		static bool _projectionMod;

		static glm::mat4 _viewMat;
		static glm::mat4 _projectionMat;

		static glm::mat4 _viewprojMat;
	};
}

#endif // PROTOTYPE_HPP
