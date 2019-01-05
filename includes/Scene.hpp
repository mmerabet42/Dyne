#ifndef SCENE_HPP
# define SCENE_HPP

# include <map>
# include <vector>

namespace dn
{
	// i really like forward declaration
	class Shader;
	class Model;
	class ModelInstance;
	class Texture;
	class Object;
	class MeshRenderer;
	class Camera;

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
	typedef std::vector<dn::MeshRenderer *> vector_MeshRenderer;
	typedef std::map<dn::Texture *, dn::vector_MeshRenderer> map_Texture;
	typedef std::pair<dn::ModelInstance *, dn::map_Texture> pair_ModelInstance;
	typedef std::map<dn::Model *, dn::pair_ModelInstance> map_Model;
	typedef std::map<dn::Shader *, dn::map_Model> map_Shader;
	// Without the typedefs it would look like this
//	std::map<dn::Shader *,
//		std::map<dn::Model *,
//			std::pair<dn::ModelInstance,
//				std::map<dn::Texture *,
//					std::vector<dn::MeshRenderer *>>>>>

	class Scene
	{
	public:
		Scene();

		// Once the object is added to the scene, its MeshRenderer, if it has one,
		// is linked to its Shader and Model
		void addObject(dn::Object *p_object);

		void start();
		void update();
		void render();

		dn::map_Shader instances() const;

	private:
		dn::map_Shader _instances;

		// _instances[mesh->shader()][mesh->model()].first->bind()
		// _instances[mesh->shader()][mesh->model()].second[mesh->texture()] ...
		// a map of maps of pairs of maps of vectors basically lol

		// The list of object
		std::vector<dn::Object *> _objects;
		dn::Camera *_camera;

		bool _started;
	};
}

#endif // SCENE_HPP
