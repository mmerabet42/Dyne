#ifndef SCENE_HPP
# define SCENE_HPP

# include <vector>
# include <map>

# include "System.hpp"
# include "Object.hpp"

namespace dn
{
	class Scene
	{
	public:
		Scene();

		template <typename S>
		void addSystem();

		void addObject(dn::Object &p_object);

		void start();
		void update();

		void objectUpdated(dn::Object *p_object);

	private:
		std::vector<dn::Object *> _objects;
		std::map<size_t, dn::SystemBase<> *> _systems;

		bool _started;
	};
}

# include "Scene.inl"

#endif // SCENE_HPP
