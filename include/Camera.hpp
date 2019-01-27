#ifndef DN_CAMERA_HPP
# define DN_CAMERA_HPP

# include "glm/matrix.hpp"
# include "Component.hpp"

namespace dn
{
	class Transform;

	class Camera: public dn::Component
	{
	public:
		Camera(
				const float &p_fov = 70.f,
				const float &p_near = 0.02f,
				const float &p_far = 100.f,
				const float &p_aspectRatio = 1.f);

		float fov() const;
		float &fov();
		void setFov(const float &p_fov);

		float far() const;
		float &far();
		void setFar(const float &p_far);

		float near() const;
		float &near();
		void setNear(const float &p_near);

		float aspectRatio() const;
		float &aspectRatio();
		void setAspectRatio(const float &p_aspectRatio);

		glm::mat4 &projectionMat();
		glm::mat4 &viewMat();

		glm::mat4 &viewProjectionMat();

		void setTransform(dn::Transform *p_transform);

	private:
		dn::Transform *_transform;

		float _fov;
		float _far;
		float _near;
		float _aspectRatio;

		glm::mat4 _projectionMat;
		glm::mat4 _viewMat;

		glm::mat4 _viewProjectionMat;
	};
}

#endif // DN_CAMERA_HPP
