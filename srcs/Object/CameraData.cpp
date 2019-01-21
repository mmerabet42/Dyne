#include "Camera.hpp"
#include "Transform.hpp"
#include "Object.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/transform.hpp"

dn::CameraData::CameraData(const float &p_fov, const float &p_near, const float &p_far, const float &p_aspectRatio)
	: ComponentData(),  _fov(p_fov), _far(p_far), _near(p_near), _aspectRatio(p_aspectRatio)
{

}

// Get and set the camera's field of view
float dn::CameraData::fov() const { return (this->_fov); }
float &dn::CameraData::fov() { return (this->_fov); }
void dn::CameraData::setFov(const float &p_fov)
{
	this->_fov = p_fov;
}

// Get and set the camera's far plane
float dn::CameraData::far() const { return (this->_far); }
float &dn::CameraData::far() { return (this->_far); }
void dn::CameraData::setFar(const float &p_far)
{
	this->_far = p_far;
}

// Get and set the camera's near plane
float dn::CameraData::near() const { return (this->_near); }
float &dn::CameraData::near() { return (this->_near); }
void dn::CameraData::setNear(const float &p_near)
{
	this->_near = p_near;
}

// Get and set the camera's aspect ratio (usually the width divided by the height of the window)
float dn::CameraData::aspectRatio() const { return (this->_aspectRatio); }
float &dn::CameraData::aspectRatio() { return (this->_aspectRatio); }
void dn::CameraData::setAspectRatio(const float &p_aspectRatio)
{
	this->_aspectRatio = p_aspectRatio;
}

// Camera's projection matrix
glm::mat4 &dn::CameraData::projectionMat()
{
	// The projection matrix is created using the perspective function of the glm library
	this->_projectionMat = glm::perspective(this->_fov, this->_aspectRatio, this->_near, this->_far);
	return (this->_projectionMat);
}

// Camera's view matrix
glm::mat4 &dn::CameraData::viewMat()
{
	// The camera needs the transform component of the object it is attached to,
	// if there is no transform component, the function does nothing
	if (this->_transform)
	{
		this->_viewMat = glm::lookAt(
			this->_transform->position(),
			this->_transform->position() + this->_transform->forward(),
			this->_transform->up());
	}
	return (this->_viewMat);
}

// Camera's view projection matrix
glm::mat4 &dn::CameraData::viewProjectionMat()
{
	// It is just the multiplication of the projection and view matrices
	this->_viewProjectionMat = this->projectionMat() * this->viewMat();
	return (this->_viewProjectionMat);
}

void dn::CameraData::setTransform(dn::TransformData *p_transform)
{
	this->_transform = p_transform;
}
