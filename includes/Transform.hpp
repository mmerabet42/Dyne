#ifndef TRANSFORM_HPP
# define TRANSFORM_HPP

# include "glm/matrix.hpp"
# include "Component.hpp"

namespace dn
{
	class Transform: public dn::Component
	{
	public:
		Transform(
				dn::Transform *p_parent,
				const glm::vec3 &p_position = glm::vec3(0.f, 0.f, 0.f),
				const glm::vec3 &p_rotation = glm::vec3(0.f, 0.f, 0.f),
				const glm::vec3 &p_scale = glm::vec3(1.f, 1.f, 1.f));

		Transform(
				const glm::vec3 &p_position = glm::vec3(0.f, 0.f, 0.f),
				const glm::vec3 &p_rotation = glm::vec3(0.f, 0.f, 0.f),
				const glm::vec3 &p_scale = glm::vec3(1.f, 1.f, 1.f));

		Transform(
				dn::Transform *p_parent,
				const float &p_xPos, const float &p_yPos = 0.f, const float &p_zPos = 0.f,
				const float &p_xRot = 0.f, const float &p_yRot = 0.f, const float &p_zPot = 0.f,
				const float &p_xScl = 1.f, const float &p_yScl = 1.f, const float &p_zScl = 1.f);

		Transform(
				const float &p_xPos, const float &p_yPos = 0.f, const float &p_zPos = 0.f,
				const float &p_xRot = 0.f, const float &p_yRot = 0.f, const float &p_zPot = 0.f,
				const float &p_xScl = 1.f, const float &p_yScl = 1.f, const float &p_zScl = 1.f);

		dn::Transform *parent() const;
		void setParent(dn::Transform *p_parent);

		glm::vec3 position() const;
		glm::vec3 &position();

		glm::vec3 rotation() const;
		glm::vec3 &rotation();

		glm::vec3 scale() const;
		glm::vec3 &scale();

		glm::mat4 &positionMat();
		glm::mat4 &rotationMat();
		glm::mat4 &scaleMat();

		glm::mat4 &transformMat();

		glm::vec3 forward();
		glm::vec3 up();
		glm::vec3 right();

		void lookAt(const glm::vec3 &p_target);

	private:
		dn::Transform *_parent;

		glm::vec3 _position;
		glm::vec3 _rotation;
		glm::vec3 _scale;

		glm::mat4 _positionMat;
		glm::mat4 _rotationMat;
		glm::mat4 _scaleMat;
		glm::mat4 _transformMat;
	};
}

#endif // TRANSFORM_HPP
