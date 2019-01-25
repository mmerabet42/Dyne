#ifndef SCENE_HPP
# define SCENE_HPP

# include <vector>
# include <map>

# include "System.hpp"
# include "Object.hpp"

namespace dn
{
	class Window;

	class Scene
	{
	public:
		Scene();
		~Scene();

		template <typename S>
		void addSystem();

		void addObject(dn::Object &p_object);

		void start();
		void update();

		void objectUpdated(dn::Object *p_object);

		dn::Window *window() const;
		void setWindow(dn::Window *p_window);

	private:
		std::vector<dn::Object *> _objects;
		std::map<size_t, dn::SystemBase<> *> _systems;

		dn::Window *_window;

		bool _started;
	};
}

# include "Scene.inl"

#endif // SCENE_HPP
