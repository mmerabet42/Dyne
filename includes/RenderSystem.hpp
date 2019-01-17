#ifndef RENDERSYSTEM_HPP
# define RENDERSYSTEM_HPP

# include "System.hpp"

struct MeshFilter: public dn::SystemFilter<dn::Transform, dn::Mesh>
{
	dn::Transform *transform;
	dn::MeshRenderer *mesh;
};
struct CameraFilter: public dn::SystemFilter<dn::Camera>
{
	dn::Camera *camera;
};

template <typename 

class RenderSystem: public dn::System<MeshFilter, CameraFilter>
{
	dn::Camera *main;

public:

	void onNewObject<MeshFilter>(MeshFilter &meshFilter)
	{
		meshFilter->transform->position() = dn::Vector3f(0.f, 0.f, 0.f);
	}

	void onNewObject<CameraFilter>(CameraFilter &cameraFilter)
	{
		main = cameraFilter->camera;
	}

	void start() { }

	void update()
	{
		std::vector<MeshFilter &> meshEntities = getEntities<MeshFilter>();
		for (MeshFilter &mesh : meshEntities)
		{
			
		}
	}
};

#endif
