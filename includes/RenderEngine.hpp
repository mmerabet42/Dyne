#ifndef DN_RENDERENGINE_HPP
# define DN_RENDERENGINE_HPP

# include <memory>

# include "Transform.hpp"
# include "Mesh.hpp"
# include "Camera.hpp"
# include "ModelInstance.hpp"
# include "Engine.hpp"

namespace dn
{
	struct MeshFilter: public dn::EngineFilter<dn::MeshFilter,
		dn::Transform, dn::Mesh>
	{
		dn::Transform *transform;
		dn::Mesh*mesh;
	};

	struct CameraFilter: public dn::EngineFilter<dn::CameraFilter,
		dn::Camera, dn::Transform>
	{
		dn::Camera *camera;
		dn::Transform *transform;
	};

	class Shader;
	class Model;
	class Texture;

	// Maybe the strangest thing you have seen today
	// Basically a Shader plus a Model generates a ModelInstance.
	// And each MeshRenderer (of each object) added to the scene is assigned
	// to a ModelInstance, but one ModelInstance can have multiple MeshRenderer.
	// The reason for this is that, in general, when you create let's say 100 cubes
	// they all uses the same model, so it is useless to create 100 ModelInstance.
	// It is better to create one ModelInstance for the 100 cubes, so the Model (vao, vbo etc.)
	// is bound only once per frame. I am aware that this is definetely not the
	// best optimization, but it is a first step, and definetely better than
	// my previous version which was binding the shader, the model vao and textures
	// for each cubes.
	namespace layer
	{
		typedef std::vector<dn::MeshFilter *> MeshFilter;
		typedef std::vector<dn::InstanceData> InstanceData;
		typedef std::pair<dn::layer::MeshFilter, dn::layer::InstanceData> MeshFilterInstanceData;
		typedef std::map<dn::Texture *, dn::layer::MeshFilterInstanceData> Texture;
		typedef std::pair<std::shared_ptr<dn::ModelInstance>, dn::layer::Texture> ModelInstance;
		typedef std::map<dn::Model *, dn::layer::ModelInstance> Model;
		typedef std::map<dn::Shader *, dn::layer::Model> Shader;
	}
	// Without the typedefs it would look like this
	//	std::map<dn::Shader *,
	//		std::map<dn::Model *,
	//			std::pair<dn::ModelInstance *,
	//				std::map<dn::Texture *,
	//					std::pair<std::vector<dn::MeshRenderer *>,
	//						std::vector<dn::IntanceData>>>>>

	class RenderEngine: public dn::Engine<dn::MeshFilter, dn::CameraFilter>
	{
	public:

		void onObjectAdded(dn::MeshFilter &p_filter);
		void onObjectRemoved(dn::MeshFilter &p_filter);

		void onObjectAdded(dn::CameraFilter &p_filter);
		void onObjectRemoved(dn::CameraFilter &p_filter);

		void onUpdate();
	private:
		dn::layer::Shader _instances;
		dn::Camera *_camera;
	};
}

#endif // DN_RENDERENGINE_HPP
