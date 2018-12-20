#include "Transform.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/transform.hpp"
#include "glm/gtx/quaternion.hpp"

dn::Transform::Transform(
		dn::Transform *p_parent,
		const glm::vec3 &p_position,
		const glm::vec3 &p_rotation,
		const glm::vec3 &p_scale)
	: Component("Transform"), _parent(p_parent), _position(p_position), _rotation(p_rotation), _scale(p_scale) { }

dn::Transform::Transform(
		const glm::vec3 &p_position,
		const glm::vec3 &p_rotation,
		const glm::vec3 &p_scale)
	: Transform(nullptr, p_position, p_rotation, p_scale) { }

dn::Transform::Transform(
		dn::Transform *p_parent,
		const float &p_xPos, const float &p_yPos, const float &p_zPos,
		const float &p_xRot, const float &p_yRot, const float &p_zRot,
		const float &p_xScl, const float &p_yScl, const float &p_zScl)
	: Component("Transform"), _parent(p_parent), _position(p_xPos, p_yPos, p_zPos), _rotation(p_xRot, p_yRot, p_zRot), _scale(p_xScl, p_yScl, p_zScl) { }

dn::Transform::Transform(
		const float &p_xPos, const float &p_yPos, const float &p_zPos,
		const float &p_xRot, const float &p_yRot, const float &p_zRot,
		const float &p_xScl, const float &p_yScl, const float &p_zScl)
	: Transform(nullptr, p_xPos, p_yPos, p_zPos, p_xRot, p_yRot, p_zRot, p_xScl, p_yScl, p_zScl) { }

dn::Transform *dn::Transform::parent() const { return (this->_parent); }
void dn::Transform::setParent(dn::Transform *p_parent)
{
	this->_parent = p_parent;
}

glm::vec3 dn::Transform::position() const { return (this->_position); }
glm::vec3 &dn::Transform::position() { return (this->_position); }

glm::vec3 dn::Transform::rotation() const { return (this->_rotation); }
glm::vec3 &dn::Transform::rotation() { return (this->_rotation); }

glm::vec3 dn::Transform::scale() const { return (this->_scale); }
glm::vec3 &dn::Transform::scale() { return (this->_scale); }

glm::mat4 &dn::Transform::positionMat()
{
	this->_positionMat = glm::translate(this->_position);
	return (this->_positionMat);
}

glm::mat4 &dn::Transform::rotationMat()
{
	this->_rotationMat = glm::toMat4(glm::quat(this->_rotation));
	return (this->_rotationMat);
}

glm::mat4 &dn::Transform::scaleMat()
{
	this->_scaleMat = glm::scale(this->_scale);
	return (this->_scaleMat);
}

glm::mat4 &dn::Transform::transformMat()
{
	this->_transformMat = this->positionMat() * this->rotationMat() * this->scaleMat();
	if (this->_parent)
		this->_transformMat = this->_parent->transformMat() * this->_transformMat;
	return (this->_transformMat);
}

glm::vec3 dn::Transform::forward()
{
	return (this->rotationMat() * glm::vec4(0.f, 0.f, -1.f, 0.f));
}

glm::vec3 dn::Transform::up()
{
	return (this->rotationMat() * glm::vec4(0.f, 1.f, 0.f, 0.f));
}

glm::vec3 dn::Transform::right()
{
	return (this->rotationMat() * glm::vec4(1.f, 0.f, 0.f, 0.f));
}

void dn::Transform::lookAt(const glm::vec3 &p_target)
{
	this->_rotation = this->rotationMat() * glm::vec4(glm::normalize(this->_position - p_target), 0.f);
}

void dn::Transform::start() { }
void dn::Transform::update() { }
