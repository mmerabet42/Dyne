#ifndef DN_SCENE_HPP
# define DN_SCENE_HPP

# include <vector>
# include <map>

# include "dn/Engine.hpp"

namespace dn
{
	class Window;
	class Object;

	class Scene
	{
	public:
		Scene();
		~Scene();

		template <typename E, typename ... Args>
		void addEngine(Args && ... p_args);

		void addObject(dn::Object &p_object);

		void start();
		void update();

		void updateEngines(dn::Object *p_object);
		void updateUObject(dn::Object *p_object);

		dn::Window *window() const;
		void setWindow(dn::Window *p_window);

	private:
		std::vector<dn::Object *> _objects;
		std::vector<dn::Object *> _uobjects;

		std::map<size_t, dn::EngineBase<> *> _engines;

		dn::Window *_window;

		bool _started;
	};
}

# include "dn/Scene.inl"

#endif // DN_SCENE_HPP
